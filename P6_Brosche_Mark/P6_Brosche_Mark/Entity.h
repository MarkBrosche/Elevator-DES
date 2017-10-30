#pragma once

typedef double Time;

class Entity
{
public:
	Entity(Time arrivalTime);
	/*
		Entity
			Parameters:
				Time	arrivalTime		arrival time of entity into the system
			Return value:
				none
			Behavior:
				Constructor for Entity object. Sets its unique ID and arrival time
	*/

	int GetID();
	/*
		GetID
			Paramters:
				none
			Return value:
				Entity ID number
			Behavior:
				gets the Entity unique ID number
	*/

	Entity();

	void setDepartureTime(Time departureTime);
	/*
		setDepartureTime
			Parameters:
				Time	departureTime	departure time of entity from system
			Return value:
				none
			Behavior:
				sets the entity's departure time from the system*/

	void setServiceStartTime(Time serviceStartTime);
	/*
		setServiceStartTime
			Parameters:
				Time	serviceStartTime	time service starts for the entity
			Return value:
				none
			Behavior:
				sets the service start time for an entity
	*/

	Time getArrivalTime();
	/*
		getArrivalTime
			Parameters:
				none
			Return value:
				entity arrival time in the system
			Behavior:
				gets the entity arrival time in the system
	*/

	Time getDepartureTime();
	/*
		getDepartureTime
			Parameters:
				none
			Return value:
				returns the entity departure time from the system
			Behavior:
				gets the entity departure time from the system
	*/

	Time getServiceStartTime();
	/*
		getServiceStartTime
			Parameters:
				none
			Return value:
				entity service start time
			Behavior:
				gets the entity's service start time
	*/

private:
	int _id;
	static int _nextID;
	Time _arrivalTime;
	Time _departureTime;
	Time _serviceStartTime;
};
