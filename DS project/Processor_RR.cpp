#include"Processor_RR.h"
Processor_RR::Processor_RR(int N, int id, string name, scheduler* p, int rtf, int rrslice) :Processor(N, id, name, p), RRslice(rrslice)
{
	RTF = rtf;
	LeftRRslice = 0;
	numRTF = 0;
}
void Processor_RR::AddToList(Process* p)
{
	count++;
	FinishTime += p->getLeftCT();
	RDYlist.enqueue(p);
}
bool Processor_RR::RunProcess()
{
	if (RDYlist.isEmpty())
	{
		state = false;
		Runprocess = nullptr;
	}
	else
	{
		count--;
		RDYlist.dequeue(Runprocess);
		state = true;
	}
	return false;
}
int Processor_RR::ExpectedFinishTime()
{
	return FinishTime;
}
void Processor_RR::print()
{
	RDYlist.PrintList();
}
Process* Processor_RR::GetRunProcess()
{
	return Runprocess;
}
bool Processor_RR::IsRdyEmpty() { return (RDYlist.isEmpty()); }
bool  Processor_RR::GetProcessById(int id, Process*& p)
{
	return true;
}

int Processor_RR::GetRdyCount()
{
	return count;
}

void Processor_RR::set_sigkill(LinkedQueue<sigkill>& kill_queue)
{
}

void Processor_RR::removerunprocess()
{
	Runprocess = nullptr;
}
void Processor_RR::ScheduleAlgo()
{
	// first check runprocess
	if (!Runprocess)
	{
		if (!RDYlist.isEmpty())
		{
			RDYlist.dequeue(Runprocess);
			LeftRRslice = RRslice;
			FinishTime -= Runprocess->getLeftCT();
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
	/*bool b = assistant->Migration_FCFS(Runprocess);
	if (b)
	{
		Runprocess=nullptr;
		ScheduleAlgo(assistant);
		return;
	}*/
	// third excute
	Runprocess->decrementCT();
	LeftRRslice--;
	TotalBusyTime++;
	if (Runprocess->getLeftCT() == 0)
	{
		assistant->move_to_trm(Runprocess);
		Runprocess == nullptr;
	}
	else
	{
		if (LeftRRslice == 0)
		{
			RDYlist.enqueue(Runprocess);
			count++;
			Runprocess = nullptr;
		}
	}
	// fourth check for I_O request
	int ct = Runprocess->get_CT();
	int lct = Runprocess->getLeftCT();
	int ior = Runprocess->get_IO_R();
	if (ct - lct == ior)
	{
		assistant->RUNtoBLK(Runprocess);
	}
}
Process* Processor_RR::get_chosen_process()
{

	if (!Runprocess)
	{
		if (!RDYlist.isEmpty())
		{
			Process* choosen;
			RDYlist.peek(choosen);
			return choosen;
		}
		else
		{
			return nullptr;
		}
	}
	return Runprocess;
}