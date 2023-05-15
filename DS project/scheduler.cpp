#include"scheduler.h"
#include"Processor_SJF.h"
#include"Processor_EDF.h"
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
	mig_fcfs_to_RR_cnt = 0;
	mig_RR_to_sjf_cnt = 0;
	work_steal_count = 0;
	InputFile = new ifstream("InputFile.txt", ios::in);
	string no_rr, no_fcfs, no_sjf, no_edf;
	string S_RTF, S_MaxW, S_STL, S_Fork_Prob;
	string S_T_RR;
	*InputFile >> no_fcfs >> no_sjf >> no_rr >> no_edf >> S_T_RR >> S_RTF >> S_MaxW >> S_STL >> S_Fork_Prob;
	FCFS_no = stoi(no_fcfs);
	SJF_no = stoi(no_sjf);
	RR_no = stoi(no_rr);
	EDF_no = stoi(no_edf);
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
	no_forked = 0;
	no_sigkill = 0;
	//Ctrl_Processors = Processors.gethead();
	// we will make one list of processors divided to three parts first part for FCFS, second for SJF and the third for RR
	for (int i = 0; i < FCFS_no; i++)
	{
		Processor_FCFS* P = new Processor_FCFS(8, i + 1, "FCFS", this, MaxW, Fork_prob);
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < SJF_no; i++)
	{
		Processor_SJF* P = new Processor_SJF(8, i + 1 + FCFS_no, "SJF", this, Processes_no);
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < RR_no; i++)
	{
		Processor_RR* P = new Processor_RR(8, i + 1 + FCFS_no + SJF_no, "RR", this, RTF, T_RR);
		Processors.InsertEnd(P);
	}
	for (int i = 0; i < EDF_no; i++)
	{
		Processor_EDF* P = new Processor_EDF(8, i + 1 + FCFS_no + SJF_no + RR_no, "EDF", this, Processes_no);
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
	load_sigkill();
	Node<Processor*>* fcfs_temp = Processors.gethead();
	for (int i = 0; i < FCFS_no; i++)  // initializing kill queue in all fcfs processors
	{
		fcfs_temp->getItem()->set_sigkill(kill_queue);
		fcfs_temp = fcfs_temp->getNext();
	}
}
/*insert a process to the processor with the least CT*/
void scheduler::Add_To_Shortest_RDY(Process* p)
{
	Node<Processor*>* ptr = Processors.gethead();
	if (ptr->getItem()->IsRdyEmpty())
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
void scheduler::load_sigkill()
{
	//sigkill Times
	string kill_id, kill_time;
	sigkill s1;
	while (!InputFile->eof())
	{
		*InputFile >> kill_time >> kill_id;
		s1.Pid = stoi(kill_id);
		s1.time = stoi(kill_time);
		kill_queue.enqueue(s1);
		no_sigkill++;
	}


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
int scheduler::get_timestep()
{
	return Time_Step;
}


void scheduler::Print_output_file()
{
	OutputFile = new ofstream("Output File", ios::out);
	Node<Process*>* process_ptr = TRM_LIST.gethead();
	int avg_WT = 0, avg_RT = 0, avg_TRT = 0, total_TRT = 0;
	while (process_ptr)
	{
		Process* cur_process = process_ptr->getItem();
		*OutputFile << "TT\t" << "PID\t" << "AT\t" << "CT\t" << "IO_D\t" << "WT\t" << "RT\t" << "TRT\t";
		*OutputFile << cur_process->get_TT() << "\t" << cur_process->getPID() << "\t" << cur_process->get_CT() << "\t" <<
			cur_process->get_total_IO_D() << "\t" << cur_process->get_WT() << "\t" << cur_process->get_RT() << "\t" << cur_process->get_TRT() << "\n";
		avg_WT += cur_process->get_WT();
		avg_RT += cur_process->get_RT();
		avg_TRT += cur_process->get_TRT();
		process_ptr = process_ptr->getNext();
	}
	total_TRT = avg_TRT;
	avg_WT /= Processes_no;
	avg_RT /= Processes_no;
	avg_TRT /= Processes_no;
	*OutputFile << Processes_no << "\n";
	*OutputFile << "Avg WT = " << avg_WT << "\t";
	*OutputFile << "Avg RT = " << avg_RT << "\t";
	*OutputFile << "Avg TRT = " << avg_TRT << "\n";



	// work steal migration rtf maxw forked_per
	int MaxW = mig_fcfs_to_RR_cnt * 100 / Processes_no;
	int RTF = mig_RR_to_sjf_cnt * 100 / Processes_no;
	int work_per = work_steal_count * 100 / Processes_no;
	int forked_per = no_forked * 100 / Processes_no;
	int killed_process = no_sigkill * 100 / Processes_no;

	*OutputFile << "Migration %: \t " << "RTF= " << RTF << "%,\t" << "MaxW= " << MaxW << "%" << "\n";
	*OutputFile << "Work Steal %: " << work_per << "%" << "\n";
	*OutputFile << "Forked Process %: " << forked_per << "%" << "\n";
	*OutputFile << "killed process %:" << killed_process << "%" << "\n \n";


	*OutputFile << "Processors: " << FCFS_no + SJF_no + RR_no + EDF_no << "[ " << FCFS_no << "FCFS, " << SJF_no << "SJF, " << RR_no << "RR, " << EDF_no << "EDF]";
	*OutputFile << "\n";


	// load
	*OutputFile << "Processors Load\n";
	Node<Processor*>* processor_out = Processors.gethead();
	for (int i = 0; i < FCFS_no + SJF_no + RR_no + EDF_no; i++)
	{
		int load_per = (processor_out->getItem()->GetPload(total_TRT)) * 100;
		*OutputFile << "p" << i + 1 << "=" << load_per << "%,\t";
	}
	*OutputFile << "\n\n";


	// utilization
	*OutputFile << "Processors Utiliz\n";
	processor_out = Processors.gethead();
	float avg_util = 0;
	for (int i = 0; i < FCFS_no + SJF_no + RR_no + EDF_no; i++)
	{
		int util_per = (processor_out->getItem()->calcPutil()) * 100;
		avg_util += util_per;
		*OutputFile << "p" << i + 1 << "=" << util_per << "%,\t";
	}
	avg_util /= FCFS_no + SJF_no + RR_no + EDF_no;
	*OutputFile << "\n Avg utilization = " << avg_util << "%,\n";
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
				Pr_ptr1->getItem()->ScheduleAlgo();// this function just get the process and run it according to a specific algorithm (don't forget to remove that process from rdy list)
				if (!Pr_ptr1->getItem()->GetRunProcess()->is_forked() && Pr_ptr1->getItem()->GetRunProcess()->get_CT() < RTF)// check RR migration
				{
					Pr_ptr1->getItem()->SetState(false);
					Pr_ptr1->getItem()->GetRunProcess()->SetRunState(false);
					Migration_RR(Pr_ptr1->getItem()->GetRunProcess());
				}
				else
				{
					if (!Pr_ptr1->getItem()->GetRunProcess()->is_forked() && Pr_ptr1->getItem()->GetRunProcess()->get_CT() > MaxW)// check FCFS migration
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
		// 4- dec IO for the first process entered BLK_List requesing IO by 1
		BLK_LIST.peek(BLK_P);
		if (BLK_P)
		{
			BLK_P->set_IO_D(BLK_P->get_IO_D() - 1);
			// then check if that process has finished
			if (BLK_P->get_IO_D() == 0)
				BLK_to_RDY(BLK_P);
		}
		// 5- check if there is a Run process in RR processors want to migrate to SJF
		// get first RR processor
		for (int i = 0; i < FCFS_no + SJF_no; i++)
			Pr_ptr_RR = Pr_ptr_RR->getNext();
		while (Pr_ptr_RR)
		{
			// if CT of a process in Run State is less than RTF migrate it to the shortest SJF processor
			if (!(Pr_ptr_RR->getItem()->IsIdle()) && Pr_ptr_RR->getItem()->GetRunProcess()->get_CT() < RTF && !Pr_ptr1->getItem()->GetRunProcess()->is_forked())
			{
				mig_RR_to_sjf_cnt++;
				Migration_RR(Pr_ptr_RR->getItem()->GetRunProcess());
				Pr_ptr_RR->getItem()->SetState(false);
				Pr_ptr_RR->getItem()->GetRunProcess()->SetRunState(false);
			}
			Pr_ptr_RR = Pr_ptr_RR->getNext();
		}
		Pr_ptr_RR = Processors.gethead();
		// 6- check if there is a Run process in FCFS processors want to migrate to RR
		for (int i = 0; i < FCFS_no; i++)
		{
			// if CT of a process in Run State is less than RTF migrate it to the shortest SJF processor
			if (!(Pr_ptr_FCFS->getItem()->IsIdle()) && Pr_ptr_FCFS->getItem()->GetRunProcess()->get_CT() > MaxW && !Pr_ptr1->getItem()->GetRunProcess()->is_forked())
			{
				Migration_FCFS(Pr_ptr_FCFS->getItem()->GetRunProcess());
				mig_fcfs_to_RR_cnt++;
				Pr_ptr_FCFS->getItem()->SetState(false);
				Pr_ptr_FCFS->getItem()->GetRunProcess()->SetRunState(false);
			}
			Pr_ptr_FCFS = Pr_ptr_FCFS->getNext();
		}
		Pr_ptr_FCFS = Processors.gethead();
		// 7-check for io request //made by ali
		Pr_ptr7 = Processors.gethead();
		while (Pr_ptr6)
		{
			Pr_ptr7->getItem()->checkIO_request();
			Pr_ptr7 = Pr_ptr7->getNext();
		}
		// 8- filling run list with run processes for each processor
		while (Pr_ptr5)
		{
			if (!(Pr_ptr5->getItem()->IsIdle()))// if its busy then there is a process in run state
				Run_List.InsertEnd(Pr_ptr5->getItem()->GetRunProcess());
			Pr_ptr5 = Pr_ptr5->getNext();
		}
		Pr_ptr5 = Processors.gethead();
		// 9- dec CT for each process in Run by one. (As a process in Run state Ct will dec)
		Pr_ptr6 = Run_List.gethead();
		while (Pr_ptr6)
		{
			Pr_ptr6->getItem()->set_CT(Pr_ptr6->getItem()->get_CT() - 1);
			Pr_ptr6 = Pr_ptr6->getNext();
		}
		// 10- work stealing part
		if (get_timestep() % STL == 0)
			while (worksteal())
				work_steal_count++;
		/*Console_out.PrintOutput(NEW_LIST, BLK_LIST,TRM_LIST,Processors, Time_Step, Processes_no, Term_no);*/
		Console_out.PrintOutput(Run_List, NEW_LIST, BLK_LIST, TRM_LIST, Processors, Time_Step, Processes_no, Term_no);
		Run_List.DeleteAll();
		update_TimeStep();
	}
}
bool scheduler::worksteal()
{
	Node<Processor*>* ptr = Processors.gethead();// pointer to processors
	Processor* ptr_short;
	Processor* ptr_long;
	float min_CT = 0, max_CT = 0;
	min_CT = ptr->getItem()->ExpectedFinishTime();
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
	ptr_short = ptr->getItem();
	ptr = Processors.gethead();
	max_CT = ptr->getItem()->ExpectedFinishTime();
	ptr = ptr->getNext();
	while (ptr) // get max CT
	{
		if (ptr->getItem()->ExpectedFinishTime() > min_CT)
			max_CT = ptr->getItem()->ExpectedFinishTime();
		ptr = ptr->getNext();
	}
	ptr = Processors.gethead();
	while (ptr->getItem()->ExpectedFinishTime() != min_CT)// get the processor that has max CT
		ptr = ptr->getNext();
	ptr_long = ptr->getItem();
	if (!ptr_long->get_first_process()->is_forked() && (max_CT - min_CT) / max_CT > 0.4)
	{
		ptr_long->switch_processes(ptr_short);
		return true;
	}
	return false;
}
void scheduler::RUNtoBLK(Process* p)
{
	BLK_LIST.enqueue(p);
}
int scheduler::get_mig_fcfs_to_RR_cnt()
{
	return mig_fcfs_to_RR_cnt;
}
int scheduler::get_mig_RR_to_sjf_cnt()
{
	return mig_RR_to_sjf_cnt;
}
int scheduler::get_work_steal_count()
{
	return work_steal_count;
}