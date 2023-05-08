#pragma once 
#include "Process.h"
Process::Process()
{
	left_child = nullptr;
	right_child = nullptr;
	To_Trm = false;
	forked = false;
}
void Process::AddProcess(int pid, int at, int ct, int io_count, int* IO_r, int* IO_d)
{
	Processor_id = -1;
	PID = pid;   //unique id for each process
	AT = at;     //the time when the process is ready to get scheduled
	CT = ct;     //total work time needed to run the process

	IO po;
	for (int i = 0; i < io_count; i++)
	{
		po.IO_R = IO_r[i];
		po.IO_D = IO_d[i];
		IO_queue.enqueue(po);
	}

	//rest of data members should be calculated later

	/*int RT   */  //the difference between the arrival time and first time getting processed // needs modifications
	//int TT=tt;     //time when the process finishes execution 
	//int TRT=tt-at; //total time spent from arrival time to termiantion TT-AT
	//int WT=TRT-ct; //total time a process spends in system without being executed by the cpu WT=TRT-CT

}
bool Process::can_fork()
{
	return (!left_child || !right_child);
}
int Process::get_CT()
{
	return CT;
}
int Process::get_RT()
{
	return RT;
}
int Process::get_AT()
{
	return AT;
}
int Process::getPID()
{
	return PID;
}
void Process::set_start_RUN(int first_RUN)
{
	RT = first_RUN - AT;
}
void Process::SetRunState(bool b)
{
	if (!b)
	{
		Processor_id = -1;
		RunState = b;
	}
	else
	{
		RunState = b;
	}
}
/*void Process::SetRunState(bool b)
{
	RunState = b;
}
bool Process::GetRunState()
{
	return RunState;
}
*/
void Process::set_termination_times(int tt)
{
	TT = tt;     //time when the process finishes execution 
	TRT = TT - AT; //total time spent from arrival time to termiantion TT-AT
	WT = TRT - CT; //total time a process spends in system without being executed by the cpu WT=TRT-CT


	// you can kill children here
}
void Process::Add_child(Process*& child)
{
	if (left_child == nullptr)
	{
		left_child = child;
		child->forked = true;
		return;
	}
	else if (right_child == nullptr)
	{
		right_child = child;

		child->forked = true;
		return;
	}
	return;
}

void Process::REC_kill_children(Process*& left, Process*& right)
{
	if (!left_child&&!right_child)
	{
		return;
	}
	else if(right_child&&!left_child)
	{
		right_child->To_Trm = true;
		REC_kill_children(right->left_child, right->right_child);
	}
	else if(left_child&&!right_child)
	{
		left_child->To_Trm = true;
		REC_kill_children(left->left_child,left->right_child);
		
	}
	else
	{
		left_child->To_Trm = true;
		right_child->To_Trm = true;
		REC_kill_children(left->left_child, left->right_child);
		REC_kill_children(right->left_child, right->right_child);
	}
}


void Process::kill_children()
{
	REC_kill_children(left_child,right_child);
}

void Process::set_Processor_id(int n)
{
	Processor_id = n;
}

bool Process::is_forked()
{
	return forked;
}

void Process::fork_process(int& process_no, int time_step)
{
	process_no++;
	Process* child = new Process;
	child->AddProcess(process_no, time_step, CT, 0, nullptr, nullptr);
	Add_child(child);
}

int Process::getLeftCT() 
{
	return LeftCT;
}

void Process::decrementCT() 
{
	LeftCT--;
}