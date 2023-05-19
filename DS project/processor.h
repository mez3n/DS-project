#pragma once
#include"Process.h"
#include"PeriorityQueue.h"
class scheduler;
struct sigkill;
class Processor
{
protected:
	bool state;// describe the state of processor if BUSY true if IDLE false
	int ID;// each processor has ID
	string Name;// each processor has name 
	int count;// the number of processes in RDY list
	float TotalBusyTime; // for calculate total busy time along the program
	float FinishTime;// in every time process is added or removed it must be edited
	float TotalIDLETime;// for calculate total idle time along the program
	Process* Runprocess;// point to processes in run state
	const int n;// time step that processor will be out of work
	int leftn;// we will use so that we do not change n  
	scheduler* assistant;// we will use it to call function in scheduler
public:

	Processor(int N, int id, string name, scheduler* p);
	virtual void ScheduleAlgo() = 0;// determine next process to be run 
	virtual void AddToList(Process* p) = 0;//  Add new process to RDY list
	float ExpectedFinishTime();// get expected time for processor to finish to help scheduler determine which processor to choose
	virtual void print() = 0; // print process PID. UI class must call it.
	float GetPload(int TotalTRTProcesses);//Get pload for each processor
	float calcPutil();// calculate Putil for processor
	bool IsIdle();// return true if idle and return false if busy
	void removerunprocess();// set runprocess null
	Process* GetRunProcess();// function to get the process that runs in a processor
	virtual bool IsRdyEmpty() = 0;//returns if the ready list is empty or not 
	bool IsStop();// determine if the processor stop due to overheaten take probability 5%
	virtual int GetRdyCount() = 0;  //returns count of ready processes
	virtual bool GetProcessById(int id, Process*& p) = 0;// it takes id and : returns true if found and the process by reference / returns false and sent process sent by ref as NULL (don't forget to remove it from rdy list)
	virtual ~Processor() {};
	virtual void set_sigkill(LinkedQueue<sigkill>& kill_queue) = 0;
	virtual int getProcessorId()
	{
		return ID;
	}
	friend ostream& operator << (ostream& out, Processor* P);


	virtual void SetState(bool b)

	{
		state = b;
	}
	virtual void kill_sig(int timestep) = 0;
	virtual Process* getprocessbyidfcfs(int id) = 0;
	virtual Process* get_first_process() = 0;// function returns the process chosen to run
	void checkIO_request();
	virtual void switch_processes(Processor*& p) = 0;
	virtual void overheat_check() = 0;// check overheat if there is overheat move all process to another rdylist and count when processor work again
	void UpdateProcessor();// update TotalBusyTime and TotalIDLETime 
};