#pragma once
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
	virtual void AddToList() = 0;//  Add new process to RDY list
	virtual int ExpectedFinishTime() = 0;// get expected time for processor to finish to help scheduler determine which processor to choose
	virtual void print() = 0; // print process PID. UI class must call it .

};

