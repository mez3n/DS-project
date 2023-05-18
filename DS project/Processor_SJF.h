#pragma once
#include "processor.h"
struct sigkill;
class Processor_SJF :public Processor
{
private:
	PeriorityQueue<Process*>* RDYlist;
public:

	Processor_SJF(int N, int id, string name, scheduler* p, int MAX_SIZE);
	void ScheduleAlgo();// determine next process to be run
	Process* getprocessbyidfcfs(int id) { return NULL; }
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	void print(); // print process PID. UI class must call it .
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	void kill_sig(int timestep);
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)	
	~Processor_SJF();
	void set_sigkill(LinkedQueue<sigkill>& kill_queue);
	int GetRdyCount();
	//implement it
	Process* get_first_process() ;// function returns the process chosen to run
	void overheat_check();
	void switch_processes(Processor*& p);
};