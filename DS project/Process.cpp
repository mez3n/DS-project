#pragma once 
#include "Process.h"
void Process::AddProcess(int pid, int at,int ct,int io_count, int* IO_r, int* IO_d)
{
	Processor_id = -1;
	 PID=pid;   //unique id for each process
	 AT=at;     //the time when the process is ready to get scheduled
	 CT=ct;     //total work time needed to run the process
	
	IO po;
	for (int i = 0; i < io_count; i++)
	{
		po.IO_R = IO_r[i];
		po.IO_D = IO_d[i];
		IO_queue.enqueue(po);
	}

	//rest of data members should be calculated later

	/*int RT   */  //the difference between the arrival time and first time getting processed // needs modifications
	//int TT=tt;     //time when the process finishes execution 
	//int TRT=tt-at; //total time spent from arrival time to termiantion TT-AT
	//int WT=TRT-ct; //total time a process spends in system without being executed by the cpu WT=TRT-CT
	
}
int Process::get_CT()
{
	return CT;
}
void Process::set_CT(int c)
{
	CT = c;
}
int Process::get_RT()
{
	return RT;
}
int Process::get_AT()
{
	return AT;
}
int Process::getPID() 
{
	return PID;
}
void Process::set_start_RUN(int first_RUN)
{
	RT = first_RUN-AT;
}
void Process::SetRunState(bool b)
{
	if (!b)
	{
		Processor_id = -1;
		RunState = b;
	}
	else
	{
		RunState = b;
	}
}
/*void Process::SetRunState(bool b)
{
	RunState = b;
}
bool Process::GetRunState()
{
	return RunState;
}
*/
void Process::set_termination_times(int tt)
{
 TT=tt;     //time when the process finishes execution 
 TRT=TT-AT; //total time spent from arrival time to termiantion TT-AT
 WT=TRT-CT; //total time a process spends in system without being executed by the cpu WT=TRT-CT
}
void Process::Add_child(Process* & child)
{
	El_3yal.add(child);
}

bool Process::is_parent()
{
	return !El_3yal.isEmpty();
}

void Process::kill_children()
{
	El_3yal.~BinaryNodeTree(); // needs modifications
}

void Process::set_Processor_id(int n)
{
	Processor_id = n;
}
