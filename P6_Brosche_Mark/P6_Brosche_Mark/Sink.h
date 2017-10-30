#pragma once

#include <string>
#include "Entity.h"

class Sink
{
public:
	Sink(std::string name);
	/*
		Sink
			Parameters:
				string	name	the name of the entity departing
			Return value:
				none
			Behavior:
				Constructor for the sink class
	*/

	void Depart(Entity *en);
	/*
		Depart
			Parameters:
				Entity	*en	pointer to the departing entity
			Return value:
				none
			Behavior:
				identifies the entity departing the application
	*/

	int TotalEntitiesProcessed();
	Time AverageFlowTime();
	Time MaxFlowTime();
	Time GetEndTime();
	

private:
	std::string _name;
	int _totalEntitiesProcessed;
	Time _totalFlowTime;
	Time _maxFlowTime;
	Time _flowTime;
	Time _endTime;
};
