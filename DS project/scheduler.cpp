#include<iostream>
#include"scheduler.h"
using namespace std;
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
	InputFile = new ifstream("InputFile.txt");
	string processes_no;
	*InputFile >> processes_no;
	Processes_no = stoi(processes_no);
	string no_rr, no_fcfs, no_sjf;
	*InputFile >> no_fcfs, no_sjf, no_rr;
	FCFS_no = stoi(no_fcfs);
	SJF_no = stoi(no_sjf);
	RR_no = stoi(no_rr);

	//====================================================================================// inputfile is up 
	Time_Step = 0;
	Ctrl_Processors = Processors.gethead();
	string process_no;
	// we will make one list of processors divided to three parts first part for FCFS, second for SJF and the third for RR
	for (int i = 0; i < FCFS_no; i++)
	{
		Processor_FCFS* P = new Processor_FCFS;
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < SJF_no; i++)
	{
		Processor_SJF* P = new Processor_SJF;
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < RR_no; i++)
	{
		Processor_RR* P = new Processor_RR;
		Processors.InsertEnd(P);
	}
	// fill the processes list
	for (int i = 0; i < Processes_no; i++)
	{
		int pid, no_IO, at, rt, ct;
		int* IO_r; int* IO_d;
		/*IO.LoadProcesses(pid,no_IO,at,rt,ct,IO_r,IO_d);*/
		// all of this is string you should use stoi()
	// any string has S before its name

	// constructor of processor class should be called here 
		string Spid, Sat, Srt, Sct, Stt, Sno_IO, SIO; //each process specifications 
		*InputFile >> Sat >> Spid >> Sct >> Sno_IO >> SIO;
		no_IO = stoi(Sat);
		at = stoi(Sat);
		rt = stoi(Srt);
		ct = stoi(Sct);
		no_IO = stoi(Sno_IO);
		pid = stoi(Spid);
		int* IO_R = new int[no_IO] {0};
		int* IO_D = new int[no_IO] {0};
		int j = 0;
		for (int i = 0; i < SIO.length(); i++)  //processing the IO string 
		{
			if (isdigit(SIO[i]))
			{
				if (SIO[i - 1] == '(')
				{
					while (isdigit(SIO[i]))
					{
						IO_R[j] = IO_R[j] * 10 + SIO[i];
						i++;
					}

				}
				else
				{
					while (isdigit(SIO[i]))
					{
						IO_D[j] = IO_D[j] * 10 + SIO[i];
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
		Process* p = new Process;
		p->AddProcess(pid, no_IO, at, rt, ct, IO_R, IO_D);
	}
}




// this function will be used in phase 2
// 
// insert a process to the processor with the least CT
//void scheduler::NewToRdy(Process* p) 
//{
//	Node<Processor*>* ptr = Processors.gethead();
//	int min_CT = ptr->getItem()->ExpectedFinishTime();
//	ptr = ptr->getNext();
//	while (ptr)
//	{
//		if (ptr->getItem()->ExpectedFinishTime() < min_CT)
//			min_CT = ptr->getItem()->ExpectedFinishTime();
//		ptr = ptr->getNext();
//	}
//	ptr = Processors.gethead();
//	while (ptr)
//	{
//		if (ptr->getItem()->ExpectedFinishTime() == min_CT)
//		{
//			ptr->getItem()->AddToList(p);
//		}
//	}
//}




// we will complete filling the rdy lists
void scheduler::simulate_system()
{
	int NO_Generated;// number generated for a run process
	Process* p = nullptr;
	Process* p1 = nullptr;// temporary pointer to move from blk to rdy
	Process* p2 = nullptr;// temporary pointer to a process from rdy list
	Process* Run_P = nullptr;// pointer to get the run process in a processor
	Node<Processor*>* Pr_ptr1 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr2 = Processors.gethead();// a pointer to processors list
	Node<Processor*>* Pr_ptr3 = Processors.gethead();// a pointer to processors list

	NEW_LIST.peek(p);
	while (TRM_LIST.getcount() != Processes_no)// stop when all processes move to trm list
	{
		// in each timestep we check:
		// 1- processes with this time step will transfer them to the rdy list. Note: we won't make any balance in this phase
		if (!NEW_LIST.isEmpty())
		{
			while (p->get_AT() == Time_Step)
			{
				NEW_LIST.dequeue(p);
				AddToRdy(p);
				NEW_LIST.peek(p);
			}
		}
		// 2- Check the RDY lists and move one process from each RDY list to RUN state of its processor. This is done if the processor is IDLE. If the processor is BUSY the process should wait in the RDY list.
		while (Pr_ptr1)
		{
			if (!(Pr_ptr1->getItem()->IsRdyEmpty()) && Pr_ptr1->getItem()->IsIdle())
			{
				Pr_ptr1->getItem()->RunProcess();// dont forget to make the process run state to be true
				// note : as shown in the project document that when a process move to run state it won't be in the ready list anymore
			}
			Pr_ptr1 = Pr_ptr1->getNext();
		}
		Pr_ptr1 = Processors.gethead();
		// 3- For each process in RUN state, Generate a random number from 1 to 100.
		while (Pr_ptr2)
		{
			if (!Pr_ptr2->getItem()->IsIdle())// if there is a process in the run state
			{
				Run_P = Pr_ptr2->getItem()->GetRunProcess();// get thr run process
				NO_Generated = GenerateNo();// generate a number for that process
				if (1 <= NO_Generated && NO_Generated <= 50)
					BLK_LIST.enqueue(Run_P);
				else
					if (20 <= NO_Generated && NO_Generated <= 30)
						Pr_ptr2->getItem()->AddToList(Run_P);
					else
						if (50 <= NO_Generated && NO_Generated <= 60)
							TRM_LIST.InsertEnd(Run_P);
			}
			Pr_ptr2 = Pr_ptr2->getNext();
		}
		Pr_ptr2 = Processors.gethead();
		// 4- For the process at the top of the BLK list, Generate a random number from 1 to 100. If this number is less than 10, move the process from BLK to RDY
		if (!BLK_LIST.isEmpty())
		{
			NO_Generated = GenerateNo();
			if (NO_Generated < 10)
			{
				BLK_LIST.dequeue(p1);
				AddToRdy(p1);
			}
		}
		// 5- For the processes in the FFS RDY list, randomly pick any process in the list and terminate it. This can be done by generating a random ID and checking if this ID is in any RDY list then kill it.
		NO_Generated = 1 + (rand() % Processes_no);
		for (int i = 0; i < FCFS_no; i++)
		{
			if (!(Pr_ptr3 ->getItem()->IsRdyEmpty()) && Pr_ptr3->getItem()->GetProcessById(NO_Generated, p2))
				TRM_LIST.InsertEnd(p2);
			Pr_ptr3 = Pr_ptr3->getNext();
		}



		update_TimeStep();
	}
}
int scheduler::GenerateNo()
{
	return 1 + (rand() % 100);
}
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
void scheduler::AddToRdy(Process* p)
{
	if (Ctrl_Processors)
	{
		Ctrl_Processors->getItem()->AddToList(p);
		Ctrl_Processors = Ctrl_Processors->getNext();
	}
	else
		Ctrl_Processors = Processors.gethead();
}
void scheduler::update_TimeStep()
{
	Time_Step++;
}
