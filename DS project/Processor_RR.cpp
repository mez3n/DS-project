#include"Processor_RR.h"
#include"scheduler.h"
#include<cstdlib>
#include"time.h"
Processor_RR::Processor_RR(int N, int id, string name, scheduler* p, int rrslice) :Processor(N, id, name, p), RRslice(rrslice)
{
	LeftRRslice = 0;
}
void Processor_RR::AddToList(Process* p)
{
	count++;
	FinishTime += p->getLeftCT();
	RDYlist.enqueue(p);
}
void Processor_RR::print()
{
	RDYlist.PrintList();
}
void Processor_RR::kill_sig(int timestep)
{

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
			state = true;
			if (Runprocess->get_RT() == -1)
			{
				Runprocess->set_RT(assistant->get_timestep());
			}
		}
		else
		{
			state = false;
		}
	}
	else 
	{
		state = true;
		if (LeftRRslice == 0)
		{
			FinishTime += Runprocess->getLeftCT();
			RDYlist.enqueue(Runprocess);
			RDYlist.dequeue(Runprocess);
			FinishTime += Runprocess->getLeftCT();
			LeftRRslice = RRslice;
			if (Runprocess->get_RT() == -1)
			{
				Runprocess->set_RT(assistant->get_timestep());
			}
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
	}
	else 
	{
		srand(time(0));
		int  r = 1+(rand()%100);
		if (r <= 5 && r > 0 )
		{
			FinishTime = 0;
			leftn = n;
			if (Runprocess)
			{
				assistant->Add_To_Shortest_RDY(Runprocess);
				Runprocess = nullptr;
				state = false;
			}
			Process* p;
			while (!RDYlist.isEmpty()) //modified (not added)
			{
				RDYlist.dequeue(p);
				assistant->Add_To_Shortest_RDY(p);
			}
		}
	}
}
void Processor_RR::switch_processes(Processor*& p)
{
	// check implement please (a function that take take the first process in (this) and give it to p)
	Process* px;
	RDYlist.dequeue(px);
	count--;
	FinishTime -= px->getLeftCT();
	p->AddToList(px);
}