#pragma once
#include "processor.h"
#include"PeriorityQueue.h"
class Processor_EDF :public Processor
{
private:
	PeriorityQueue<Process*>* RDYlist;
	int num;//number of process finished before they deadline
public:
	Processor_EDF(int MAX_SIZE);
	//void ScheduleAlgo();// determine next process to be run
	bool RunProcess();// edit cpu time for process and return true if process need I/O ->to do
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose-> to do
	void print(); // print process PID. UI class must call it .
	//float calcPload();// calculate Pload for processor
	float GetPload();//Get pload for each processor->to do
	//float calcPutil();// calculate Putil for processor
	//bool removefromlist(Process*& p);// remove process from ready list 
	//bool peeknextprocess(Process*& p);// return the the next process but not remove it from list
	bool IsIdle();// return true if idle and return false if busy->to do
	Process* GetRunProcess();// function to get the process that runs in a processor->to do
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	//bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	//bool checkdeadline(int currenttimestep);// the scheduler must pass current time step for scheduleAlgo which will call this function to determine if process finish before its deadline
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)->to do
	/*bool printProcessor();*/
	~Processor_EDF();
};
