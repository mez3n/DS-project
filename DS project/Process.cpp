#pragma once 
#include"Process.h"
Process::Process()
{
	left_child = nullptr;
	right_child = nullptr;
	To_Trm = false;
	forked = false;
	fork_count = 0;
	RT = -1;
	total_IO_D = 0;
	in_trm = false;
	WT = 0;
	TRT = 0;
	TT = 0;
}
void Process::AddProcess(int pid, int at, int ct, int io_count, int* IO_r, int* IO_d)
{
	Processor_id = -1;
	PID = pid;   //unique id for each process
	AT = at;     //the time when the process is ready to get scheduled
	CT = ct;     //total work time needed to run the process
	LeftCT = ct;
	IO* po = new IO;
	for (int i = 0; i < io_count; i++)
	{
		po->IO_R = IO_r[i];
		po->IO_D = IO_d[i];
		IO_queue.enqueue(po);
		total_IO_D += po->IO_D;
	}

	//rest of data members should be calculated later

	/*int RT   */  //the difference between the arrival time and first time getting processed // needs modifications
	//int TT=tt;     //time when the process finishes execution 
	//int TRT=tt-at; //total time spent from arrival time to termiantion TT-AT
	//int WT=TRT-ct; //total time a process spends in system without being executed by the cpu WT=TRT-CT

}



bool Process::can_fork()
{
	return fork_count<2;
}
int Process::get_CT()
{
	return CT;
}
int Process::get_RT()
{
	return RT;
}
int Process::get_TT()
{
	return TT;
}

int Process::get_TRT()
{
	return TRT;
}

void Process::set_WT(int newwt)
{
	WT = newwt;
}

int Process::get_WT()
{
	return WT;
}

int Process::get_total_IO_D()
{
	return total_IO_D;
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
	in_trm = true;
	SetRunState(false);
	kill_children();
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



void Process::REC_kill_children(Process*& parent)
{
	if ((!parent)||(parent->in_trm))
	{
		return;
	}
	parent->To_Trm = true;
	REC_kill_children(parent->left_child);
	REC_kill_children(parent->right_child);
	parent->left_child = nullptr;
	parent->right_child = nullptr;
}




void Process::kill_children()
{
	if (is_forked())
	{
		REC_kill_children(left_child);
		REC_kill_children(right_child);
		left_child = nullptr;
		right_child = nullptr;
	}
}

void Process::set_Processor_id(int n)
{
	Processor_id = n;
}

bool Process::is_forked()
{
	return forked;
}

Process* Process::fork_process(int& process_no, int time_step)
{
	if (fork_count < 2)
	{
		process_no++;
		Process* child = new Process;
		child->AddProcess(process_no, time_step, LeftCT, 0, nullptr, nullptr);// I think it should be Left CT 
		Add_child(child);
		fork_count++;
		forked = true;
		return child;
	}
	return nullptr;
}

bool Process::orphan()
{
	return To_Trm;
}

int Process::getLeftCT()
{
	return LeftCT;
}

void Process::decrementCT()
{
	LeftCT--;
}

void Process::remove_first_io()
{
	IO* p;
	IO_queue.dequeue(p);
}
int &Process::get_IO_D() // please implement it, function get IO_D for a process
{
	IO *p;
	IO_queue.peek(p);
	return p->IO_D;
}
void Process::set_IO_D(int c) // please implement it, function set IO_D for a process 
{
	IO*p;
	IO_queue.peek(p);
	p->IO_D = c;
}
void Process::set_CT(int c)
{
	CT = c;
}

int Process::getdeadline()
{
	return Deadline;
}
int Process::get_IO_R() // please implement it, function get IO_R for a process
{
	IO *p;
	if (IO_queue.peek(p))
	{
		return p->IO_R;
	}
	else
	{
		return -1;
	}
}

void Process::set_RT(int current_time)
{
	RT =current_time-AT;
}


