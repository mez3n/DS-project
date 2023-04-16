#pragma once
#include "Processor.h"
#include"Linkedqueue.h"
#include"scheduler.h"
class Processor_RR :public Processor
{
private:
	LinkedQueue<Process*> RDYlist;
	int RTF;// if a process has CT less than RTF it should be moved to SJF RDYlist
	int numRTF;// number of processes migrated
	int RRslice;// time slice for each process to be excuted
	int LeftRRslice;// this will help me determine if the time slice ended or not
public:
	Processor_RR();
	void ScheduleAlgo();// determine next process to be run
	bool RunProcess();// edit cpu time for process and return true if process need I/O ->to do
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose-> to do
	void print(); // print process PID. UI class must call it .
	float calcPload();// calculate Pload for processor
	float GetPload();//Get pload for each processor->to do
	float calcPutil();// calculate Putil for processor
	bool removefromlist(Process*& p);// remove process from ready list 
	bool peeknextprocess(Process*& p);// return the the next process but not remove it from list
	bool IsIdle();// return true if idle and return false if busy->to do
	Process* GetRunProcess();// function to get the process that runs in a processor->to do
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	void migration();
	~Processor_RR() {};
};
