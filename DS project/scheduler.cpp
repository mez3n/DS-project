#include<iostream>
#include"scheduler.h"
using namespace std;
scheduler::scheduler()
{
	IO.get_counts(FCFS_no, SJF_no, RR_no, Processes_no);
	// we will make one list of processors divided to three parts first part for FCFS, second for SJF and the third for RR
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
		int pid, no_IO, at, rt, ct, tt;
		int* IO_r, int* IO_d;
		IO.LoadProcesses(pid, no_IO, at, rt, ct, IO_r, IO_d);
		Process p;
		p.AddProcess(pid, no_IO, at, rt, ct, IO_r, IO_d);// please update process class as mentioned in the pdf so I can continue // Done
		Processes.enqueue(p);
	}
}
