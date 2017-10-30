#include "Source.h"
#include <iostream>

using namespace std;

class Source::CreateEntityEvent : public Event
{
public:
	CreateEntityEvent(Source *source)
	{
		_source = source;
	}

	void Execute()
	{
		_source->CreateEntity();
	}

private:
	Source *_source;
};

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime)
{
	_sssq = sssq;
	_interarrivalTime = interarrivalTime;

	//schedule first event creation as part of initialization
	ScheduleEventAt(0.0, new CreateEntityEvent(this));

	_name = name;
	_numGen = -1;
}

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime, int numGen)
{
	_sssq = sssq;
	_interarrivalTime = interarrivalTime;

	//schedule first event creation as part of initialization
	ScheduleEventAt(0.0, new CreateEntityEvent(this));

	_name = name;
	_numGen = numGen;
}

void Source::CreateEntity()
{
	if ((_numGen == -1) || (_numGen > 0))
	{
		if (_numGen > 0)
		{
			_numGen--;
		}

		//create a new entity and assign arrival time to the system
		Entity *en = new Entity(GetCurrentSimTime());

		cout << GetCurrentSimTime() << ", " << _name << ", CreateEntity, Entity " << en->GetID() << endl;

		//schedule entity arrival at the SSSQ
		_sssq->ScheduleArrivalIn(0.0, en);

		//schedule the next arrival event
		ScheduleEventIn(_interarrivalTime->GetRV(), new CreateEntityEvent(this));
	}
}
