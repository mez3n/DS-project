#include "Process.h"

void Process::AddProcess(int pid, int at, int rt, int ct, int tt)
{
	int PID=pid;   //unique id for each process
	int AT=at;     //the time when the process is ready to get scheduled
	int RT=rt;     //the difference between the arrival time and first time getting processed
	int CT=ct;     //total work time needed to run the process
	int TT=tt;     //time when the process finishes execution 
	int TRT=tt-at; //total time spent from arrival time to termiantion TT-AT
	int WT=TRT-ct; //total time a process spends in system without being executed by the cpu WT=TRT-CT
}
