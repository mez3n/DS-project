#include"Processor_FCFS.h"
Processor_FCFS::Processor_FCFS(int N, int id, string name,scheduler* p, int maxw, float fork) :Processor(N, id, name,p)
{
	MaxW = maxw;
	Fork = fork;
	numMaxW = 0;
	ArrSigKill =nullptr;
}
void Processor_FCFS::set_sigkill(int* sigkill)
{
	ArrSigKill = sigkill;
}
void Processor_FCFS::AddToList(Process* p)
{
	count++;
	state = true;
	FinishTime += p->get_CT();
	RDYlist.InsertEnd(p);
}
bool Processor_FCFS::RunProcess()
{
	if (RDYlist.isEmpty())
	{
		state = false;
		Runprocess = nullptr;
	}
	else
	{
		count--;
		RDYlist.DeleteFirst(Runprocess);
		state = true;
	}
	return false;
}
int Processor_FCFS::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_FCFS::print()
{
	RDYlist.PrintList();
}
float Processor_FCFS::GetPload(int TotalTRTProcesses)
{
	return(TotalBusyTime / TotalTRTProcesses);
}
bool Processor_FCFS::IsIdle()
{
	if (Runprocess == nullptr)
		state = false;
	return!state;
}
Process* Processor_FCFS::GetRunProcess()
{
	return Runprocess;
}
bool Processor_FCFS::IsRdyEmpty() { return (RDYlist.isEmpty()); }
bool  Processor_FCFS::GetProcessById(int id, Process*& p)
{
	p = nullptr;
	LNode<Process*>* ptr = RDYlist.getbrain();
	while (ptr)
	{
		if (ptr->getItem()->getPID() == id)
		{
			p = ptr->getItem();
			RDYlist.MoveProcess(ptr->getItem());
			return true;
		}
		ptr = ptr->getNext();
	}
	return false;
}

int Processor_FCFS::GetRdyCount()
{
	return count;
}
void Processor_FCFS::removerunprocess()
{
	Runprocess = nullptr;
}

void Processor_FCFS::ScheduleAlgo() 
{
	// first check runprocess
	if (!Runprocess) 
	{
		if (!RDYlist.isEmpty())
		{
			RDYlist.DeleteFirst(Runprocess);
			count--;
		}
		else 
		{
			state = false;
			TotalIDLETime++;
			return;
		}
	}
	// second check Migration
	/*bool b = p->Migration_FCFS(Runprocess);
	if (b)
	{
	    Runprocess=nullptr;
		ScheduleAlgo(p);
		return;
	}*/
	// third  check fork
	/*p->Fork(Runprocess); */
	// fourth excute
	Runprocess->decrementCT();
	TotalBusyTime++;
	if (Runprocess->getLeftCT() == 0) 
	{
		/*p->AddToTRM(Runprocess);*/
		Runprocess == nullptr;
	}
	// fifth check for I_O request
Process* Processor_FCFS::getprocessbyidfcfs(int id)
{
	LNode<Process*>* ptr = RDYlist.getbrain();
	Process* p = NULL;
	while (ptr)
	{
		if (ptr->getItem()->getPID() == id)
		{
			p = ptr->getItem();
			RDYlist.MoveProcess(ptr->getItem());
			count--;
			return p;
		}
		ptr = ptr->getNext();
	}
	return p;

}
