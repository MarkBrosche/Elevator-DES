#pragma once
#include "Simulation.h"
#include "Distribution.h"
#include "Sink.h"
#include <string>

class SSSQ : public SimObj
{
public:
	SSSQ(std::string name, Sink *sink, Distribution *serviceTime);
	/*
		SSSQ
			Parameters:
				string			name			provides the name of the SSSQ object
				Sink			*sink			provides a pointer to the Sink object to dispose of entities
				Distribution	*serviceTime	how long for the service time of an entity
			Return value:
				none
			Behavior:
				constructor for SSQ object that initializes the private variables 
				and keeps track of departure times
	*/

	void ScheduleArrivalIn(Time deltaT, Entity *en);
	/*
		ScheduleArrivalIn
			Parameters:
				Time	deltaT	time increment for when the arrival is scheduled
				Entity	*en		the entity that is arriving
			Return Value:
				none
			Behavior:
				schedules the arrival of an entity to the SSSQ system
	*/

	Time TotalServiceTime();
	/*
		TotalServiceTime
			Parameters:
				none
			Return value:
				total service time for the server
			Behavior:
				gets the total service time of the server
	*/

	int TotalEntitiesArrived();
	Time AverageDelayInQueue();
	Time MaxDelayInQueue();

private:
	//State Variables
	Time _SSSQAvailability, _prevServiceStartTime;
	Sink *_sink;
	Distribution *_serviceTime;
	std::string _name;
	Time _totalServiceTime;
	int _totalentitiesarrived;
	Time 	_totalDelayInQueue,	_maxDelayInQueue, _delayInQueue;

	
	//Events
	class ArriveEvent;
	class DepartEvent;

	//Event Methods
	void Arrive(Entity *en);
	/*
		Arrive
			Parameters:
				Entity	*en		Entity that is arriving
			Return value:
				none
			Behavior:
				computes the departure time of the entity that has arrived 
				based on its random service time
	*/

	void Depart(Entity *en);
	/*
		Depart
			Parameters:
				Entity	*en		Entity that is leaving the service point
			Return value:
				none
			Behavior:
				logs the departure of the entity from the service area
	*/
};
