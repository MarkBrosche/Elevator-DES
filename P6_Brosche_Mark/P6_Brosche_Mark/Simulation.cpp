#include "Simulation.h"
#include "Entity.h"
#include <iostream>

using namespace std;

class SimObj::EventSet
{
public:
	EventSet()
	{
		_first = 0;		//initialized the pointer to the head EventNode 

	}

	void AddEvent(Time time, Event *ev)
	{
		EventNode *en = new EventNode(time, ev);
		if (_first == 0)
		{
			_first = en;						//if this is the first event, add it to the EventSet and point to it.
		}
		else if (time < _first->_time)
		{
			en->_next = _first;					//if this event is before the next event then add it to the front of the EventSet
			_first = en;
		}
		else
		{
			EventNode *current = _first;
			while ((current->_next == 0) ? false : (current->_next->_time <= time))		//adds node to middle of EventSet
			{
				current = current->_next;
			}
			en->_next = current->_next;
			current->_next = en;
		}
	}

	Event *GetEvent()
	{
		//return the next event in the event set based on simulation time

		Event *ev = _first->_ev;
		EventNode *en = _first;
		_first = _first->_next;
		return ev;
	}

	Time GetTime()
	{
		return _first->_time;
	}

	bool HasEvent()
	{
		return (_first != 0);
	}

private:
	struct EventNode
	{
		EventNode(Time time, Event *ev)
		{
			_time = time;			//time that this event should be executed
			_ev = ev;				//event associated with this node
			_next = 0;				//pointer to the next event in the sequence of events
		}
		Time _time;
		Event *_ev;
		EventNode *_next;
	};
	EventNode *_first;				//pointer to the first event in the EventSet
};

Time SimObj::GetCurrentSimTime()
{
	return SimObj::_currentTime;	//returns the current simulation time
}

void SimObj::RunSimulation()
{
	while (SimObj::_eventSet.HasEvent())
	{
		SimObj::_currentTime = SimObj::_eventSet.GetTime();
		Event *ev = SimObj::_eventSet.GetEvent();

		//execute the code associated with the event
		ev->Execute();		
	}
}

void SimObj::RunSimulation(Time endTime)
{
	SimObj::_endTime = endTime; //set endtime of simulation
	while ((SimObj::_eventSet.HasEvent()) ? (SimObj::_eventSet.GetTime() <=
		endTime) : false)
	{
		SimObj::_currentTime = SimObj::_eventSet.GetTime();
		Event *ev = SimObj::_eventSet.GetEvent();

		//execute the code associated with the event
		ev->Execute();
	}

}

Time SimObj::_currentTime = 0.0;	//initializes simulation time to zero at the start of the simulation
Time SimObj::_endTime = 0.0;	//initializes simulation endtime to zero at the start of the simulation

SimObj::EventSet SimObj::_eventSet;	//instantiates the eventSet at the start of the simulation


SimObj::SimObj()
{
}

void SimObj::ScheduleEventIn(Time deltaTime, Event * ev)
{
	//add the event to the event set
	_eventSet.AddEvent(_currentTime + deltaTime, ev);
}

void SimObj::ScheduleEventAt(Time time, Event * ev)
{
	//add the event to the event set
	_eventSet.AddEvent(time, ev);
}

Time SimObj::GetEndTime()
{
	//returns the end time of the simulation
	return SimObj::_endTime;
}
