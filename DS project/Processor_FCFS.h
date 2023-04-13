#pragma once
#pragma once
#include "processor.h"
#include"LinkedList.h"
template<class T>
class Processor_FCFS :public processor
{
private:
	LinkedList<T> RDYlist;
public:
	void ScheduleAlgo();// determine next process to be run
	bool RunProcess();// edit cpu time for process and return true if process need I/O
	void AddToList();//  Add new process to RDY list
	int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose
	void print(); // print process PID. UI class must call it .
	void Migration();// search for process which may migrate to another processor
	void killOrphans();// search for orphans and remove them
};

