#pragma once
#include"scheduler.h"
#include"Process.h"
class Processor
{
private:
	bool state;// describe the state of processor if BUSY true if IDLE false
	int count;// the number of processors in RDY list
	int TotalBusyTime; // for calculate total busy time along the program
	// pointer to process in run state 
public:
	virtual void ScheduleAlgo() = 0;// determine next process to be run
	virtual bool RunProcess() = 0;// edit cpu time for process and return true if process need I/O
	virtual void AddToList(Process* p) = 0;//  Add new process to RDY list
	virtual int ExpectedFinishTime() = 0;// get expected time for processor to finish to help scheduler determine which processor to choose
	virtual void print() = 0; // print process PID. UI class must call it .
	virtual int GetPload() = 0;// Get pLoad for each processor
	virtual bool IsIdle() = 0;// return true if idle and return false if busy
	virtual Process* GetRunProcess() = 0;// function to get the process that runs in a processor
	virtual bool GetProcessById(int id,Process* p) = 0;// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
        virtual bool IsRdyEmpty() = 0;//returns if the ready list is empty or not
};
