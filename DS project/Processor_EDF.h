#pragma once
#include "processor.h"
#include"LinkedQueue.h"
template<class T>
class EDF :public Processor
{
private:
	LinkedQueue<T> RDYlist;
public:
	void ScheduleAlgo();// determine next process to be run
	bool RunProcess();// edit cpu time for process and return true if process need I/O
	void AddToList();//  Add new process to RDY list
	int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose
	void print(); // print process PID. UI class must call it .
};

