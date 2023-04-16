#pragma once
#include"scheduler.h"
#include"Process.h"
class Processor
{
protected:
	bool state;// describe the state of processor if BUSY true if IDLE false
	int count;// the number of processors in RDY list
	int TotalBusyTime; // for calculate total busy time along the program
	int FinishTime;// in every time process is added or removed it must be edited
	int TotalIDLETime;// for calculate total idle time along the program
	int TotalTRTProcesses;// calc total turn around time for all processes enter the processor
	Process* Runprocess;// point to processes in run state
	int n;// time step that processor will be out of work 
public:
	Processor();
	virtual void ScheduleAlgo() = 0;// determine next process to be run
	virtual bool RunProcess() = 0;// edit cpu time for process and return true if process need I/O 
	virtual void AddToList(Process* p) = 0;//  Add new process to RDY list
	virtual int ExpectedFinishTime() = 0;// get expected time for processor to finish to help scheduler determine which processor to choose
	virtual void print() = 0; // print process PID. UI class must call it.
	virtual float calcPload() = 0;// calculate Pload for processor
	virtual float GetPload() = 0;//Get pload for each processor
	virtual float calcPutil() = 0;// calculate Putil for processor
	virtual bool removefromlist(Process*& p) = 0;// remove process from ready list 
	virtual bool peeknextprocess(Process*& p) = 0;// return the the next process but not remove it from list
	virtual bool IsIdle() = 0;// return true if idle and return false if busy
	virtual Process* GetRunProcess() = 0;// function to get the process that runs in a processor
	virtual bool IsRdyEmpty() = 0;//returns if the ready list is empty or not 
	virtual bool IsStop()=0;// determine if the processor stop due to overheaten take probability 5%
	virtual bool GetProcessById(int id, Process*& p) = 0;// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
	virtual ~Processor() {};
	/*virtual bool printProcessor() = 0;*/
};