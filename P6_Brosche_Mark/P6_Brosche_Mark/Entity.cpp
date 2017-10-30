#include "Entity.h"

int Entity::_nextID = 1;

Entity::Entity(Time arrivalTime)
{
	//assign a unique id to the entity and increment the id counter
	_id = _nextID++;

	//log the entity arrival time
	_arrivalTime = arrivalTime;
}

int Entity::GetID()
{
	return _id;
}

Entity::Entity()
{
	_id = _nextID++;
}

void Entity::setDepartureTime(Time departureTime)
{
	_departureTime = departureTime;
}

void Entity::setServiceStartTime(Time serviceStartTime)
{
	_serviceStartTime = serviceStartTime;
}

Time Entity::getArrivalTime()
{
	return _arrivalTime;
}

Time Entity::getDepartureTime()
{
	return _departureTime;
}

Time Entity::getServiceStartTime()
{
	return _serviceStartTime;
}
