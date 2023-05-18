#pragma once
#include "Processor.h"
#include"Linkedqueue.h"
struct sigkill;
class Processor_RR :public Processor
{
private:
	LinkedQueue<Process*> RDYlist;
	const int RRslice;// time slice for each process to be excuted
	int LeftRRslice;// this will help me determine if the time slice ended or not
public:

	Processor_RR(int N, int id, string name, scheduler* p,int rrslice);
	void ScheduleAlgo();// determine next process to be run
	Process* getprocessbyidfcfs(int id) { return NULL; }
	void AddToList(Process* p);//  Add new process to RDY list-> to do
	void print(); // print process PID. UI class must call it .
	void kill_sig(int timestep) ;
	bool IsRdyEmpty();//returns if the ready list is empty or not ->
	bool GetProcessById(int id, Process*& p);// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)->to do
	~Processor_RR() {};
	void set_sigkill(LinkedQueue<sigkill>& kill_queue);
	int GetRdyCount();
	//implement it
	Process* get_first_process() ;// function returns the process chosen to run
	void overheat_check();
	void switch_processes(Processor*& p);
};