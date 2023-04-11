#ifndef PROCESS_
#define PROCESS_
#include"Linkedqueue.h"
struct IO
{
	int IO_R; // Request time
	int IO_D; // Duration time
		
};
class Process  // scheduler class should have a list of all processes
{
private:
	int PID; //unique id for each process
	int AT;  //the time when the process is ready to get scheduled
	int RT;  //the difference between the arrival time and first time getting processed
	int CT;  //total work time needed to run the process
	int TT;  //time when the process finishes execution 
	int TRT; //total time spent from arrival time to termiantion TT-AT
	int WT;  //total time a process spends in system without being executed by the cpu WT=TRT-CT
	LinkedQueue<IO> IO_queue;
public:
	void AddProcess(int pid, int at, int rt, int ct,int io_count, int* IO_r, int* IO_d); // will get called by scheduler class in a loop to load each process
	
};




















#endif
