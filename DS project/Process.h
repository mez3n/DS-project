#pragma once 
#ifndef PROCESS_
#define PROCESS_
#include"Linkedqueue.h"
#include"BinaryNodeTree.h"





struct IO
{
	int IO_R; // Request time
	int IO_D; // Duration time

};

class Process  // scheduler class should have a list of all processes
{
private:
	int PID; //unique id for each process
	int AT;  //the time when the process is ready to get scheduled
	int RT;  //the difference between the arrival time and first time getting processed
	int CT;  //total work time needed to run the process
	int TT;  //time when the process finishes execution 
	int TRT; //total time spent from arrival time to termiantion TT-AT
	int WT;  //total time a process spends in system without being executed by the cpu WT=TRT-CT
	bool RunState;// get run state for a process
	int LeftCT;// we don't want to change CT for output file so we use this
	int Deadline;// the expected deadline for process
	int Processor_id; //id of the processor running the process else it is -1 
	LinkedQueue<IO> IO_queue; // storage for all IO 
	Process* left_child, * right_child;  //forking data members it represents a tree with a parent pointer 
	bool forked;
	void Add_child(Process*& child);
	void REC_kill_children(Process*& left, Process*& right); // recursive function of kill orph
	bool To_Trm;
public:
	Process();
	void AddProcess(int pid, int at, int ct, int io_count, int* IO_r, int* IO_d);// will get called by scheduler class in a loop to load each process
	bool can_fork();
	int get_CT();
	int get_RT();
	int get_AT();
	int getPID();
	int getLeftCT();
	void decrementCT();
	void set_start_RUN(int start);   // when the process eun for the first time set this function with the time step
	void SetRunState(bool b);
	//bool GetRunState();
	void set_termination_times(int tt); //calculated after termination and calculates TRT and WT by default
	bool is_parent();
	void kill_children(); //KILL_ORPH name just for fun I don't actually kill children IRL :D 
	void set_Processor_id(int n);
	bool is_forked();
	void fork_process(int& process_no, int time_step);

	friend ostream& operator << (ostream& out, Process* P);
};


#endif




















