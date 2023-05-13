#pragma once
#include "processor.h"
#include"PeriorityQueue.h"
struct sigkill;
class Processor_EDF :public Processor
{
private:
	PeriorityQueue<Process*>* RDYlist;
public:

	Processor_EDF(int N, int id, string name, scheduler* p, int MAX_SIZE);
	void ScheduleAlgo();// determine next process to be run
	Process* getprocessbyidfcfs(int id) { return NULL; }
	bool RunProcess();// edit cpu time for process and return true if process need I/O ->to do
	void AddToList(Process* p);//  Add new process to RDY list
	void print(); // print process PID. UI class must call it 
	bool removefromlist(Process*& p);// remove process from ready list 
	bool peeknextprocess(Process*& p);// return the the next process but not remove it from list
	Process* GetRunProcess();// function to get the process that runs in a processor->to do
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	void set_sigkill(LinkedQueue<sigkill>& kill_queue);
	bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
	~Processor_EDF();
	int GetRdyCount();
	void removerunprocess();
	//implement it
	Process* get_chosen_process() ;// function returns the process chosen to run
};