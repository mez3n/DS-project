#include"Processor_RR.h"
#include"scheduler.h"
#include<cstdlib>
#include"time.h"
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
	if (!Runprocess)
	{
		if (!RDYlist.isEmpty())
		{
			RDYlist.dequeue(Runprocess);
			LeftRRslice = RRslice;
			FinishTime -= Runprocess->getLeftCT();
			count--;
			TotalBusyTime++;
			state = true;
		}
		else
		{
			state = false;
			TotalIDLETime++;
		}
	}
	else 
	{
		TotalBusyTime++;
		state = true;
		if (LeftRRslice == 0)
		{
			FinishTime += Runprocess->getLeftCT();
			RDYlist.enqueue(Runprocess);
			RDYlist.dequeue(Runprocess);
			FinishTime += Runprocess->getLeftCT();
			LeftRRslice = RRslice;
		}
	}
	if(LeftRRslice > 0)
	    LeftRRslice--;
}
Process* Processor_RR::get_first_process()
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
void Processor_RR::overheat_check() 
{
	if (leftn > 0)
	{
		leftn--;
		TotalIDLETime++;
		state = false;
	}
	else 
	{
		srand(time(0));
		int  r = 1+(rand()%100);
		if (r <= 5 && r > 0 )
		{
			leftn = n;
			if (Runprocess)
			{
				assistant->Add_To_Shortest_RDY(Runprocess);
				Runprocess = nullptr;
				state = false;
			}
			Process* p;
			while (RDYlist.isEmpty()) 
			{
				RDYlist.dequeue(p);
				assistant->Add_To_Shortest_RDY(Runprocess);
			}
		}
	}
}