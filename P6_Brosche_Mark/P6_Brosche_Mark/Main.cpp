#include "Simulation.h"
#include <iostream>
#include "Distribution.h"
#include "Sink.h"
#include "SSSQ.h"
#include "Source.h"

using namespace std;

void main()
{
	double endTime = 500.0;
	
	Sink sink("Sink");

	SSSQ sssq("SSSQ", &sink, new Exponential(1));

	Source source("Source", &sssq, new Poisson(2));

	SimObj::RunSimulation(endTime);					//runs the simulation to a specific end time

	//Display DES Performance Measures
	cout << "Total Entities Arrived in Queue: " << sssq.TotalEntitiesArrived() << endl;

	cout << "Total Entities Processed in Simulation: " << sink.TotalEntitiesProcessed() << endl;

	cout << "Average Delay in Queue (total delay / total entities that arrived in SSSQ): " << sssq.AverageDelayInQueue() << endl;

	cout << "Maximum Delay in Queue: " << sssq.MaxDelayInQueue() << endl;

	cout << "Average Flow Time: " << sink.AverageFlowTime() << endl;

	cout << "Max Flow Time: " << sink.MaxFlowTime() << endl;

	cout << "Total Service Time: " << sssq.TotalServiceTime() << endl;

	cout << "Server Utilization: " << ((sssq.TotalServiceTime() / ((endTime == 0.0) ? sink.GetEndTime() : endTime)) * 100.0) << "%" << endl;

	cout << "<enter> to terminate: ";
	cin.get();											//pauses the simulation to keep the window open
}