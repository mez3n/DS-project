#include "Process.h"

void Process::AddProcess(int pid, int at, int rt, int ct,int io_count, int* IO_r, int* IO_d)
{
	int PID=pid;   //unique id for each process
	int AT=at;     //the time when the process is ready to get scheduled
	int RT=rt;     //the difference between the arrival time and first time getting processed
	int CT=ct;     //total work time needed to run the process

	IO po;
	for (int i = 0; i < io_count; i++)
	{
		po.IO_R = IO_r[i];
		po.IO_D = IO_d[i];
		IO_queue.enqueue(po);
	}

	//rest of data members should be calculated later

	//int TT=tt;     //time when the process finishes execution 
	//int TRT=tt-at; //total time spent from arrival time to termiantion TT-AT
	//int WT=TRT-ct; //total time a process spends in system without being executed by the cpu WT=TRT-CT
	
}
int Process::get_CT()
{
	return CT;
}
int Process::get_RT()
{
	return RT;
}
int Process::get_AT()
{
	return AT;
}
void Process::SetRunState(bool b)
{
	RunState = b;
}
bool Process::GetRunState()
{
	return RunState;
}

void Process::set_termination_times(int tt)
{
int TT=tt;     //time when the process finishes execution 
int TRT=TT-AT; //total time spent from arrival time to termiantion TT-AT
int WT=TRT-CT; //total time a process spends in system without being executed by the cpu WT=TRT-CT
}
void Process::Add_child(Process* & child)
{
	El_3yal.add(child);
}
