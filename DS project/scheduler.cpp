#include"scheduler.h"
#include"Processor_SJF.h"
class processor;
class UI;
#ifndef NODE_
#define NODE_
template<class T>
class Node {
	T item;
	Node* next;
public:
	Node() {};
	Node(T newItem); //non-default constructor
	void setItem(T a)
	{
		item = a;
	}
	T getItem() const
	{
		if (this == NULL)
		{
			return 0;
		}
		return item;
	}
	void setNext(Node<T>* n)
	{
		next = n;
	}
	Node<T>* getNext() const
	{
		return next;
	}
};
#endif

scheduler::scheduler()
{
	// anything with S before its name is a data member in string
	InputFile = new ifstream("InputFile.txt", ios::in);
	string no_rr, no_fcfs, no_sjf;
	string S_RTF, S_MaxW, S_STL, S_Fork_Prob;
	string S_T_RR;
	*InputFile >> no_fcfs >> no_sjf >> no_rr >> S_T_RR >> S_RTF >> S_MaxW >> S_STL >> S_Fork_Prob;
	FCFS_no = stoi(no_fcfs);
	SJF_no = stoi(no_sjf);
	RR_no = stoi(no_rr);
	RTF = stoi(S_RTF);
	MaxW = stoi(S_MaxW);
	STL = stoi(S_STL);
	Fork_prob = stoi(S_Fork_Prob);
	T_RR = stoi(S_T_RR);
	string S_processes_no;
	*InputFile >> S_processes_no;
	Processes_no = stoi(S_processes_no);

	//====================================================================================// inputfile is up 
	Time_Step = 0;
	//Ctrl_Processors = Processors.gethead();
	// we will make one list of processors divided to three parts first part for FCFS, second for SJF and the third for RR
	for (int i = 0; i < FCFS_no; i++)
	{
		Processor_FCFS* P = new Processor_FCFS(8, i + 1, "FCFS",this, MaxW, Fork_prob);
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < SJF_no; i++)
	{
		Processor_SJF* P = new Processor_SJF(8, i + 1 + FCFS_no, "SJF",this, Processes_no);
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < RR_no; i++)
	{
		Processor_RR* P = new Processor_RR(8, i + 1 + FCFS_no + SJF_no, "RR",this, RTF, T_RR);
		Processors.InsertEnd(P);
	}
	// fill the processes list
	for (int i = 0; i < Processes_no; i++)
	{
		int pid, no_IO, at, rt, ct;
		int* IO_r; int* IO_d;

		// any string has S before its name

		// constructor of processor class should be called here 
		string Spid, Sat, Sct, Sno_IO; //each process specifications 
		*InputFile >> Sat >> Spid >> Sct >> Sno_IO;

		no_IO = stoi(Sat);
		at = stoi(Sat);
		ct = stoi(Sct);
		no_IO = stoi(Sno_IO);
		pid = stoi(Spid);
		int* IO_R = new int[no_IO] {0};
		int* IO_D = new int[no_IO] {0};
		int j = 0;
		char* SIO = new char[no_IO * 20];
		if (no_IO > 0)
		{
			InputFile->getline(SIO, no_IO * 10);

			string;
			for (int i = 1; SIO[i] != '\0'; i++)  //processing the IO string 
			{
				if (isdigit(SIO[i]))
				{
					if (SIO[i - 1] == '(')
					{
						while (isdigit(SIO[i]))
						{
							IO_R[j] = IO_R[j] * 10 + SIO[i] - '0';
							i++;
						}
					}
					else
					{
						while (isdigit(SIO[i]))
						{
							IO_D[j] = IO_D[j] * 10 + SIO[i] - '0';
							i++;
						}
						j++;
					}
				}
				else
				{
					continue;
				}
			}
		}
		Process* p = new Process;
		p->AddProcess(pid, at, ct, no_IO, IO_R, IO_D);
		NEW_LIST.enqueue(p);
	}
}
 /*insert a process to the processor with the least CT*/
void scheduler::Add_To_Shortest_RDY(Process* p) 
{
	Node<Processor*>* ptr = Processors.gethead();
	if(ptr->getItem()->IsRdyEmpty())
		ptr->getItem()->AddToList(p);// add process to that processor whatever its type
	else
	{
		int min_CT = ptr->getItem()->ExpectedFinishTime();
		ptr = ptr->getNext();
		while (ptr) // get min CT
		{
			if (ptr->getItem()->ExpectedFinishTime() < min_CT)
				min_CT = ptr->getItem()->ExpectedFinishTime();
			ptr = ptr->getNext();
		}
		ptr = Processors.gethead();
		while (ptr->getItem()->ExpectedFinishTime() != min_CT)// get the processor that has min CT
			ptr = ptr->getNext();
		ptr->getItem()->AddToList(p);// add process to that processor whatever its type
	}
}
//int scheduler::GenerateNo()
//{
//	return 1 + (rand() % 100);
//}
void scheduler::load_sigkill(int*& kill_arr)
{
	//sigkill Times
	string kill_id, kill_time;
	int* kill_time_arr = new int [Processes_no] {-1};  // each index in the array is a proccesor id if it is not -1 then the process should be killed at the time specified
	while (!InputFile->eof())
	{
		*InputFile >> kill_time >> kill_id;
		kill_time_arr[stoi(kill_id)] = stoi(kill_time);
	}
	kill_arr = kill_time_arr;
}

//void scheduler::AddToRdy(Process* p)
//{
//	if (Ctrl_Processors)
//	{
//		Ctrl_Processors->getItem()->AddToList(p);
//		Ctrl_Processors = Ctrl_Processors->getNext();
//	}
//	else
//		Ctrl_Processors = Processors.gethead();
//}
void scheduler::insertIN_MinRR_CT(Process* p)
{
	Node<Processor*>* Pr_RR = Processors.gethead();// a pointer to RR_processors 
	for (int i = 0; i < FCFS_no + SJF_no; i++)// get first RR processor
		Pr_RR = Pr_RR->getNext();
	int min_CT = Pr_RR->getItem()->ExpectedFinishTime();
	Pr_RR = Pr_RR->getNext();
	while (Pr_RR) // get min CT
	{
		if (Pr_RR->getItem()->ExpectedFinishTime() < min_CT)
			min_CT = Pr_RR->getItem()->ExpectedFinishTime();
		Pr_RR = Pr_RR->getNext();
	}
	Pr_RR = Processors.gethead(); 
	for (int i = 0; i < FCFS_no + SJF_no; i++)// get first RR processor
		Pr_RR = Pr_RR->getNext();
	while (Pr_RR->getItem()->ExpectedFinishTime() != min_CT)// get the processor that has min CT
		Pr_RR = Pr_RR->getNext();
	Pr_RR->getItem()->AddToList(p);// add process to that processor whatever its type
}
void scheduler::insertIN_MinSJF_CT(Process* p)
{
	Node<Processor*>* Pr_ptr_SJF = Processors.gethead();// a pointer to SJF_processors 
	for (int i = 0; i < FCFS_no; i++)// get first SJF processor
		Pr_ptr_SJF = Pr_ptr_SJF->getNext();
	int min_CT = Pr_ptr_SJF->getItem()->ExpectedFinishTime();
	Pr_ptr_SJF = Pr_ptr_SJF->getNext();
	while (Pr_ptr_SJF) // get min CT
	{
		if (Pr_ptr_SJF->getItem()->ExpectedFinishTime() < min_CT)
			min_CT = Pr_ptr_SJF->getItem()->ExpectedFinishTime();
		Pr_ptr_SJF = Pr_ptr_SJF->getNext();
	}
	Pr_ptr_SJF = Processors.gethead();
	for (int i = 0; i < FCFS_no; i++)// get first SJF processor
		Pr_ptr_SJF = Pr_ptr_SJF->getNext();
	while (Pr_ptr_SJF->getItem()->ExpectedFinishTime() != min_CT)// get the processor that has min CT
		Pr_ptr_SJF = Pr_ptr_SJF->getNext();
	Pr_ptr_SJF->getItem()->AddToList(p);// add process to that processor whatever its type
}
// migrate a run process from RR to SJF
void scheduler::Migration_RR(Process* p)
{
	insertIN_MinSJF_CT(p);
}
void scheduler::Migration_FCFS(Process* p)
{
	insertIN_MinRR_CT(p);
}
// transfer process from run list to trm list
void scheduler::move_to_trm(Process* p)
{
	p->SetRunState(false);
	TRM_LIST.InsertEnd(p);
}
void scheduler::RUN_to_TRM(Node<Processor*>*& Pr_ptr)
{
	Pr_ptr->getItem()->SetState(false);
	Pr_ptr->getItem()->GetRunProcess()->SetRunState(false);
	TRM_LIST.InsertEnd(Pr_ptr->getItem()->GetRunProcess());
}
// transfer process from BLK list to the shortest rdy list
void scheduler::BLK_to_RDY(Process*& Pr_ptr)
{
	BLK_LIST.dequeue(Pr_ptr);// remove it from blk
	Pr_ptr->remove_first_io();// remove the io from io queue of the process when it is finished and became zero
	Add_To_Shortest_RDY(Pr_ptr);// add it to the shortest rdy
}
// inc the timestep by 1
void scheduler::update_TimeStep()
{
	Time_Step++;
}
void scheduler::simulate_system()
{
	//Ctrl_Processors = Processors.gethead();
	int NO_Generated;// number generated for a run process
	Process* p = nullptr;
	Process* p1 = nullptr;// temporary pointer to move from blk to rdy
	Process* p2 = nullptr;// temporary pointer to a process from rdy list
	Process* Run_P = nullptr;// pointer to get the run process in a processor
	Process* BLK_P = nullptr;// pointer to get the the first process entered BLK requesting IO
	Node<Processor*>* Pr_ptr1 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr2 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr3 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr4 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr5 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr_RR = Processors.gethead();// pointer to RR processors
	Node<Processor*>* Pr_ptr_FCFS = Processors.gethead();// pointer to FCFS processors
	Node<Process*>* Pr_ptr6 = Run_List.gethead();// a pointer to Run list
	Node<Processor*>* Pr_ptr7 = Processors.gethead();// a pointer to processors list
	NEW_LIST.peek(p);
	while (TRM_LIST.getcount() != Processes_no)// stop when all processes move to trm list // i think that it may need modification due to forked process 
	{
		// in each timestep we check:
		// 1- processes with this time step will transfer them to the rdy list. Note: we won't make any balance in this phase
		if (!NEW_LIST.isEmpty())
		{
			while (p->get_AT() == Time_Step && !NEW_LIST.isEmpty())
			{
				NEW_LIST.dequeue(p);
				Add_To_Shortest_RDY(p);// add process to rdy lists 1,2,...
				if (!NEW_LIST.isEmpty())
					NEW_LIST.peek(p);
			}
		}
		// 2- Check the RDY lists and move one process from each RDY list to RUN state of its processor. This is done if the processor is IDLE. If the processor is BUSY the process should wait in the RDY list.
		while (Pr_ptr1)
		{
			if (!(Pr_ptr1->getItem()->IsRdyEmpty()) && Pr_ptr1->getItem()->IsIdle())
			{
				Pr_ptr1->getItem()->RunProcess();
				if (Pr_ptr1->getItem()->GetRunProcess()->get_CT() < RTF)// check RR migration
				{
					Pr_ptr1->getItem()->SetState(false);
					Pr_ptr1->getItem()->GetRunProcess()->SetRunState(false);
					Migration_RR(Pr_ptr1->getItem()->GetRunProcess());
				}
				else
				{
					if (Pr_ptr1->getItem()->GetRunProcess()->get_CT() > MaxW)// check FCFS migration
					{
						Pr_ptr1->getItem()->SetState(false);
						Pr_ptr1->getItem()->GetRunProcess()->SetRunState(false);
						Migration_FCFS(Pr_ptr1->getItem()->GetRunProcess());
					}
					else
					{
					// note : as shown in the project document that when a process move to run state it won't be in the ready list anymore
						Pr_ptr1->getItem()->GetRunProcess()->SetRunState(true);
						Pr_ptr1->getItem()->GetRunProcess()->set_Processor_id(Pr_ptr1->getItem()->getProcessorId());
					}
				}
			}
			Pr_ptr1 = Pr_ptr1->getNext();
		}
		Pr_ptr1 = Processors.gethead();
		// not needed in phase 1 but i eill keep it for now
		//// 3- For each process in RUN state, Generate a random number from 1 to 100.
		//while (Pr_ptr2)
		//{
		//	if (!Pr_ptr2->getItem()->IsIdle())// if there is a process in the run state
		//	{
		//		Run_P = Pr_ptr2->getItem()->GetRunProcess();// get thr run process
		//		NO_Generated = GenerateNo();// generate a number for that process
		//		if (1 <= NO_Generated && NO_Generated <= 15)
		//		{
		//			Pr_ptr2->getItem()->SetState(false);
		//			Pr_ptr2->getItem()->GetRunProcess()->SetRunState(false);
		//			BLK_LIST.enqueue(Run_P);
		//		}
		//		else
		//			if (20 <= NO_Generated && NO_Generated <= 30)
		//			{
		//				Pr_ptr2->getItem()->SetState(false);
		//				Pr_ptr2->getItem()->GetRunProcess()->SetRunState(false);
		//				Pr_ptr2->getItem()->AddToList(Run_P);
		//			}
		//			else
		//				if (50 <= NO_Generated && NO_Generated <= 60)
		//				{
		//					Pr_ptr2->getItem()->SetState(false);
		//					Pr_ptr2->getItem()->GetRunProcess()->SetRunState(false);
		//					TRM_LIST.InsertEnd(Run_P);
		//				}
		//	}
		//	Pr_ptr2 = Pr_ptr2->getNext();
		//}
		//Pr_ptr2 = Processors.gethead();
		// 4- For the process at the top of the BLK list, Generate a random number from 1 to 100. If this number is less than 10, move the process from BLK to RDY
		/*if (!BLK_LIST.isEmpty())
		{
			NO_Generated = GenerateNo();
			if (NO_Generated < 10)
			{
				BLK_LIST.dequeue(p1);
				AddToRdy(p1);
			}
		}*/
		// 5- For the processes in the FFS RDY list, randomly pick any process in the list and terminate it. This can be done by generating a random ID and checking if this ID is in any RDY list then kill it.
		//NO_Generated = 1 + (rand() % Processes_no);
		//for (int i = 0; i < FCFS_no; i++)
		//{
		//	if (!(Pr_ptr3->getItem()->IsRdyEmpty())/* && Pr_ptr3->getItem()->GetProcessById(NO_Generated, p2)*/)
		//	{
		//		p2 = Pr_ptr3->getItem()->getprocessbyidfcfs(NO_Generated);
		//		if (p2)
		//			TRM_LIST.InsertEnd(p2);
		//	}
		//	Pr_ptr3 = Pr_ptr3->getNext();
		//}
		//Pr_ptr3 = Processors.gethead();
		// 3- if CT for a process is finished it goes to TRM_LIST
		//------------------------------------------------------------------------------------------------------------------
		while (Pr_ptr4)
		{
			if (!(Pr_ptr4->getItem()->IsIdle()))// if its busy then there is a process in run state
				if (Pr_ptr4->getItem()->GetRunProcess()->get_CT() == 0)
					RUN_to_TRM(Pr_ptr4);
			Pr_ptr4 = Pr_ptr4->getNext();
		}
		Pr_ptr4 = Processors.gethead();
		//------------------------------------------------------------------------------------------------------------------
		// 4- filling run list with run processes for each processor
		while (Pr_ptr5)
		{
			if (!(Pr_ptr5->getItem()->IsIdle()))// if its busy then there is a process in run state
				Run_List.InsertEnd(Pr_ptr5->getItem()->GetRunProcess());
			Pr_ptr5 = Pr_ptr5->getNext();
		}
		Pr_ptr5 = Processors.gethead();
		// 5- dec CT for each process in Run by one. (As a process in Run state Ct will dec)
		Pr_ptr6 = Run_List.gethead();
		while (Pr_ptr6)
		{
			Pr_ptr6->getItem()->set_CT(Pr_ptr6->getItem()->get_CT() - 1);
			Pr_ptr6 = Pr_ptr6->getNext();
		}
		// 6- dec IO for the first process entered BLK_List requesing IO by 1
		BLK_LIST.peek(BLK_P);
		if (BLK_P)
		{
			BLK_P->set_IO_D(BLK_P->get_IO_D() - 1);
			// then check if that process has finished
			if (BLK_P->get_IO_D() == 0)
				BLK_to_RDY(BLK_P);
		}
		// 7- check if there is a Run process in RR processors want to migrate to SJF
		// get first RR processor
		for (int i = 0; i < FCFS_no + SJF_no; i++)
			Pr_ptr_RR = Pr_ptr_RR->getNext();
		while (Pr_ptr_RR)
		{
			// if CT of a process in Run State is less than RTF migrate it to the shortest SJF processor
			if (!(Pr_ptr_RR->getItem()->IsIdle()) && Pr_ptr_RR->getItem()->GetRunProcess()->get_CT() < RTF)
			{
				Migration_RR(Pr_ptr_RR->getItem()->GetRunProcess());
				Pr_ptr_RR->getItem()->SetState(false);
				Pr_ptr_RR->getItem()->GetRunProcess()->SetRunState(false);
			}
			Pr_ptr_RR = Pr_ptr_RR->getNext();
		}
		Pr_ptr_RR = Processors.gethead();
		// 8- check if there is a Run process in FCFS processors want to migrate to RR
		for (int i = 0; i < FCFS_no; i++)
		{
			// if CT of a process in Run State is less than RTF migrate it to the shortest SJF processor
			if (!(Pr_ptr_FCFS->getItem()->IsIdle()) && Pr_ptr_FCFS->getItem()->GetRunProcess()->get_CT() > MaxW)
			{
				Migration_FCFS(Pr_ptr_FCFS->getItem()->GetRunProcess());
				Pr_ptr_FCFS->getItem()->SetState(false);
				Pr_ptr_FCFS->getItem()->GetRunProcess()->SetRunState(false);
			}
			Pr_ptr_FCFS = Pr_ptr_FCFS->getNext();
		}
		Pr_ptr_FCFS = Processors.gethead();
		//9-check for io request
		Pr_ptr7 = Processors.gethead();
		while (Pr_ptr6)
		{
			Pr_ptr7->getItem()->checkIO_request();
			Pr_ptr7 = Pr_ptr7->getNext();
		}
		/*Console_out.PrintOutput(NEW_LIST, BLK_LIST,TRM_LIST,Processors, Time_Step, Processes_no, Term_no);*/
		Console_out.PrintOutput(Run_List, NEW_LIST, BLK_LIST, TRM_LIST, Processors, Time_Step, Processes_no, Term_no);
		Run_List.DeleteAll();
		update_TimeStep();
	}
}
void scheduler::RUNtoBLK(Process* p)
{
	BLK_LIST.enqueue(p);
}