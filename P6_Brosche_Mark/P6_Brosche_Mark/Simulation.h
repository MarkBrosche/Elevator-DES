#pragma once

typedef double Time;

class Event
{
public:
	Event()
	{

	}
	virtual void Execute() = 0;
};

class SimObj
{
public:
	static Time GetCurrentSimTime();
	/*
		GetCurrentSimTime
			Parameters:
				none
			Return value:
				Current simulation time
			Behavior:
				Returns the simulation time of the currently executing event
	*/

	static void RunSimulation();
	/*
		RunSimulation
			Parameters:
				none
			Return value:
				none
			Behavior:
				Executes events in time stamp order. Continues executing 
				until no future events remain to execute. Simultaneous events 
				are executed in the order they were scheduled.
	*/

	static void RunSimulation(Time endTime);
	/*
		RunSimulation
			Parameters:
				Time	endTime		Simulation time that the simulation should end.
			Return value:
				none
			Behavior:
				Executes events in time stamp order. Continues executing 
				until either the current simulation time exceeds endTime 
				or not future events remain to execute. Simultaneous events 
				are executed in the order they were scheduled.
	*/

	Time GetEndTime();
	/*
	GetEndTime
	Paramters:
	none
	Return value:
	End time of simulation
	Behavior:
	gets the end time of the simulation
	*/


protected:
	SimObj();
	/*
		SimObj
			Parameters:
				none
			Return value:
				none
			Behavior:
				Constructor, no change in state
	*/

	void ScheduleEventIn(Time deltaTime, Event *ev);
	/*
		ScheduleEVentIn
			Parameters:
				Time	time	simulation time delay before event is executed
				Event	*ev		event to be executed
			Return value:
				none
			Behavior:
				Schdedules event ev to be executed when the current simulation time
				reaches the current simulation time + deltaTime.
	*/

	void ScheduleEventAt(Time time, Event *ev);
	/*
		ScheduleEventAt
			Parameters:
				Time	time	Simulation time when the event should be executed.
				Event	*ev		event to be executed
			Return value:
				none
			Behavior:
				Schedules event ev to be executed when the current simulation time reaches time
	*/
	

private:
	static Time _currentTime;	//maintains the current time for the entire simulation
	class EventSet;				//container for all the scheduled events
	static EventSet _eventSet;	//event set for the entire simulation
	static Time _endTime;		//end time of simulation

};
