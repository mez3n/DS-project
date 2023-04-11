#include<iostream>
#include"scheduler.h"
using namespace std;
scheduler::scheduler()
{
	// we will make one list of processors divided to three parts first part for FCFS, second for SJF and the third for RR
	LoadInputs(FCFS_no, SJF_no, RR_no, Processes_no);
	for (int i = 0; i < FCFS_no; i++)
	{
		Processor_FCFS* P = new Processor_FCFS;
		ProcessorsList.InsertEnd(P);
	}
	for (int i = 0; i < SJF_no; i++)
	{
		Processor_SJF* P = new Processor_SJF;
		ProcessorsList.InsertEnd(P);
	}
	for (int i = 0; i < RR_no; i++)
	{
		Processor_RR* P = new Processor_RR;
		ProcessorsList.InsertEnd(P);
	}
	// fill the processes list
	for (int i = 0; i < Processes_no; i++)
	{
		Process p;
		p.AddProcess();// please update process class as mentioned in the pdf so i can continue
		processesList.enqueue(p);
	}
}
