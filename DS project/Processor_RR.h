#pragma once
#include "Processor.h"
#include"Linkedqueue.h"
struct sigkill;
class Processor_RR :public Processor
{
private:
	LinkedQueue<Process*> RDYlist;
	int RTF;// if a process has CT less than RTF it should be moved to SJF RDYlist
	int numRTF;// number of processes migrated
	const int RRslice;// time slice for each process to be excuted
	int LeftRRslice;// this will help me determine if the time slice ended or not
public:

	Processor_RR(int N, int id, string name, scheduler* p, int rtf, int rrslice);
	void ScheduleAlgo();// determine next process to be run
	Process* getprocessbyidfcfs(int id) { return NULL; }
	bool RunProcess();// edit cpu time for process and return true if process need I/O ->to do
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	int ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose-> to do
	void print(); // print process PID. UI class must call it .
	bool removefromlist(Process*& p);// remove process from ready list 
	bool peeknextprocess(Process*& p);// return the the next process but not remove it from list
	Process* GetRunProcess();// function to get the process that runs in a processor->to do
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)->to do
	~Processor_RR() {};
	void set_sigkill(LinkedQueue<sigkill>& kill_queue);
	void removerunprocess();
	int GetRdyCount();
	//implement it
	Process* get_chosen_process() ;// function returns the process chosen to run
};