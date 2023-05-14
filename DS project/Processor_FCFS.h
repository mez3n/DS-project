#pragma once
#include "processor.h"
#include"ListADT.h"
//#include"ProcessList.h"
struct sigkill;
class Processor_FCFS : public Processor
{
private:
	ListADT<Process*> RDYlist;
	int MaxW;// if process total waiting time exceed this number it should be moved to RR RDYlist
	int numMaxW;// number of processes migrated 
	float Fork;// it is the fork probability
	LinkedQueue<sigkill> kill_queue;  //queue of sig kill
public:

	Processor_FCFS(int N, int id, string name, scheduler* p, int maxw, float fork);
	void kill_sig(int timestep); //fucntion kills processes by sig kill each loop
	void ScheduleAlgo();// determine next process to be run
	void set_sigkill(LinkedQueue<sigkill>& kill_queue);
	bool RunProcess();   // edit cpu time for process and return true if process need I/O ->to do // PS. mazen please change its name 
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	void print(); // print process PID. UI class must call it .
	bool removefromlist(Process*& p);// remove process from ready list 
	bool peeknextprocess(Process*& p);// return the the next process but not remove it from list
	Process* GetRunProcess();// function to get the process that runs in a processor->to do
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
	~Processor_FCFS() {};
	void removerunprocess();
	int GetRdyCount();
	Process* getprocessbyidfcfs(int id);
	//implement it
	Process* get_chosen_process() ;// function returns the process chosen to run
	void overheat_check();
	void switch_processes(Processor*& p)
	{
		// check implement please (a function that take take the first process in (this) and give it to p)
		Process* px;
		RDYlist.DeleteFirst(px);
		p->AddToList(px);
	}
};