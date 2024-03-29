#pragma once
#include"Processor_FCFS.h"
#include"Processor_RR.h"
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
	//Node<Processor*>* Ctrl_Processors; // pointer to control Processors list
	ifstream* InputFile;
	ofstream* OutputFile;
	UI Console_out ;  //object of UI class needed to pass the console window information
	int FCFS_no, SJF_no, RR_no,EDF_no, Processes_no, Time_Step,Term_no;
	int RTF, MaxW, STL, Fork_prob;
	int T_RR; //time slice for RR processor
	LinkedList<Process*> Run_List;
	int no_forked;
	int no_sigkill;
	int mig_fcfs_to_RR_cnt;
	int mig_RR_to_sjf_cnt;
	int work_steal_count;
	LinkedQueue<sigkill> kill_queue;
public:
	scheduler();
	~scheduler();
	//void AddToRdy(Process* p);
	void RUN_to_TRM(Node<Processor*>*& Pr_ptr);
	void BLK_to_RDY(Process*& Pr_ptr);
	void simulate_system();// make the program ready to run
	void Add_To_Shortest_RDY(Process* p);// insert a process to the processor with the least CT (in phase 2)
	void update_TimeStep();// inc timestep by 1
	void load_sigkill();
	void Migration_RR(Process* p);
	void insertIN_MinSJF_CT(Process* p);
	void Migration_FCFS(Process* p);
	void insertIN_MinRR_CT(Process* p);
	void RUNtoBLK(Process* p);
	void move_to_trm(Process* p);
	int get_timestep(); // not sure if i will need this -- keep it I wil need it
	void Print_output_file();
	void worksteal();
	int get_mig_fcfs_to_RR_cnt();
	int get_mig_RR_to_sjf_cnt();
	int get_work_steal_count();
	bool IsAllProcessorStop();// check if all Processors are stoped
	bool IsAllFCFSstop();// check if all FCFS are stoped
	void checkForking(Process* p);// to be called by FCFS in scheduleAlgo
	void AddToShortestFCFS(Process*);// add forcked process to shortest FCFS
};
#endif

struct sigkill
{
	int Pid;
	int time;
};
