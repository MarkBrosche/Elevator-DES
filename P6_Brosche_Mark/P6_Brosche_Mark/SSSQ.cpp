#include "SSSQ.h"
#include <iostream>

using namespace std;

SSSQ::SSSQ(std::string name, Sink * sink, Distribution * serviceTime)
{
	_SSSQAvailability = 0;
	_sink = sink;
	_serviceTime = serviceTime;
	_name = name;
	_totalServiceTime = 0;
	_totalentitiesarrived = 0;
	_totalDelayInQueue = 0;
	_maxDelayInQueue = 0;
	_delayInQueue = 0;

}

class SSSQ::ArriveEvent : public Event
{
public:
	ArriveEvent(SSSQ *sssq, Entity *en)
	{
		_sssq = sssq;
		_en = en;
	}

	void Execute()
	{
		_sssq->Arrive(_en);
	}

private:
	SSSQ *_sssq;
	Entity *_en;
};

void SSSQ::ScheduleArrivalIn(Time deltaT, Entity *en)
{
	//schedule an arrive event with the Simulation Executive
	ScheduleEventIn(deltaT, new ArriveEvent(this, en));
}

Time SSSQ::TotalServiceTime()
{
	return _totalServiceTime;
}




class SSSQ::DepartEvent : public Event
{
public:
	DepartEvent(SSSQ *sssq, Entity *en)
	{
		_sssq = sssq;
		_en = en;
	}

	void Execute()
	{
		_sssq->Depart(_en);
	}

private:
	SSSQ *_sssq;
	Entity *_en;
};

void SSSQ::Arrive(Entity * en)
{
	cout << GetCurrentSimTime() << ", Call Elevator Event " << _name << ", Entity " << en->GetID() << endl;
	Time departTime;
	if (_SSSQAvailability < GetCurrentSimTime())
	{
		departTime = GetCurrentSimTime() + _serviceTime->GetRV();

		//assign service start time to entity
		en->setServiceStartTime(GetCurrentSimTime());
	}
	// Enable the simulation to serve the entire Queue that has built up since the elevator last went into Service from being Idle.
	else if(en->getArrivalTime() < _prevServiceStartTime)
	{
		departTime = _prevServiceStartTime + _serviceTime->GetRV();

		//assign service start time to entity, which should begin with all other entities waiting in queue at time of Elevator availability.
		en->setServiceStartTime(_prevServiceStartTime);
	}
	else
	{
		departTime = _SSSQAvailability + _serviceTime->GetRV();

		//assign service start time to entity, which should begin after the elevator returns from its last service call.
		en->setServiceStartTime(_SSSQAvailability);
	}
	_totalentitiesarrived++;

	//delay computation
	//compute total delay in queue time for this entity
	_delayInQueue = en->getServiceStartTime() - en->getArrivalTime();

	_totalDelayInQueue += _delayInQueue;

	//compute max delay in queue
	if (_delayInQueue > _maxDelayInQueue) 
	{
		_maxDelayInQueue = _delayInQueue;
	}

	
	
	//set entity departure time
	en->setDepartureTime(departTime);

	//set SSSQ availability time i.e. when the elevator will return from delivering previous passengers.
	_SSSQAvailability = departTime + (departTime - en->getServiceStartTime());
	//record service start time for if entity is stuck in queue.
	_prevServiceStartTime = en->getServiceStartTime();
	//schedule the departure event
	ScheduleEventAt(departTime, new DepartEvent(this, en));

	//computes total service time
	if (departTime <= SimObj::GetEndTime() || SimObj::GetEndTime() == 0) //checks if endttime is not set and if the entity departure happens before the end of simulation 
		_totalServiceTime += (en->getDepartureTime() - en->getServiceStartTime()); //if yes, add the total service time of the entity
	else
		_totalServiceTime += SimObj::GetEndTime() - en->getServiceStartTime(); // if not, add the service time of the entity until the simulation endtime
}

void SSSQ::Depart(Entity * en)
{
	
	
	cout << GetCurrentSimTime() << " , Elevator Delivery " << _name << ", Depart, Entity " << en->GetID() << endl;
	_sink->Depart(en);
	
}

int SSSQ::TotalEntitiesArrived()
{
	return _totalentitiesarrived;
}

Time SSSQ::AverageDelayInQueue()
{
	return _totalDelayInQueue / _totalentitiesarrived;
}

Time SSSQ::MaxDelayInQueue()
{
	return _maxDelayInQueue;
}
