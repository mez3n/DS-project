#pragma once
#include"Processor_FCFS.h"
#include"Processor_RR.h"
#include"Processor_SJF.h"
#include"Process.h"
#include"LinkedList.h"
#include<fstream>
#include<string>
#include "UI.h"

#ifndef SCHEDULER_
#define SCHEDULER_
class scheduler 
{
	LinkedList<Processor*> Processors; // both linkedlist or queue can be used (linkedlist more flexible) 
	LinkedQueue<Process*> NEW_LIST; // queue is used as it can maintain the processes that have been created but not yet arrived.
	LinkedQueue<Process*> BLK_LIST; // The blocked list can be implemented using a queue The processes that are waiting for I/O resources can be added to the end of the queue and when the resources become available they can be moved to the ready queue
	LinkedList<Process*> TRM_LIST; // The terminated list can be implemented using linkedlist The processes that have completed their execution can be added to the end of the linkedlist
	Node<Processor*>* Ctrl_Processors; // pointer to control Processors list
	ifstream* InputFile;
	ofstream* OutputFile;
	UI Console_out ;  //object of UI class needed to pass the console window information
	int FCFS_no, SJF_no, RR_no, Processes_no, Time_Step,Term_no;
	int RTF, MaxW, STL, Fork_prob;
	int T_RR; //time slice for RR processor
	LinkedList<Process*> Run_List;
	
public:
	scheduler();
	void AddToRdy(Process* p);
	void simulate_system();// make the program ready to run
	//void NewToRdy(Process* p);// insert a process to the processor with the least CT (in phase 2)
	void update_TimeStep();// inc timestep by 1
	int GenerateNo();// generates a number between 1:100 for a process in run list
	void LoadProcesses(int pid, int no_IO, int at, int rt, int ct, int*& IO_r, int*& IO_d); // will be called in main, the function behind reading all inputs from txt file 
	void get_counts(int& no_fcfs, int& no_sjf, int& rr, int& process_no);
	void load_sigkill(LinkedQueue<sigkill>& kill_queue);
	void move_to_trm(Process* p);
	
};

struct sigkill
{
	int Pid;
	int time;
};
#endif
