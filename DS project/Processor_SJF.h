#pragma once
#include "processor.h"
#include"LinkedQueue.h"
#include"scheduler.h"
class Processor_SJF :public Processor
{
private:
	LinkedQueue<Process*> RDYlist;
public:
	virtual void ScheduleAlgo();// determine next process to be run
	virtual bool RunProcess();// edit cpu time for process and return true if process need I/O
	virtual void AddToList(Process* p);//  Add new process to RDY list
	virtual int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose
	virtual void print(); // print process PID. UI class must call it .
	virtual int GetPload();// Get pLoad for each processor
	virtual bool IsIdle();// return true if idle and return false if busy
	virtual Process* GetRunProcess();// function to get the process that runs in a processor
	virtual bool GetProcessById(int id, Process* p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
        virtual bool IsRdyEmpty();//returns if the ready list is empty or not
};
