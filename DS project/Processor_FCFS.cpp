#include"Processor_FCFS.h"
#include"scheduler.h"
struct sigkill;
Processor_FCFS::Processor_FCFS(int N, int id, string name, scheduler* p, int maxw, float fork) :Processor(N, id, name, p)
{
	MaxW = maxw;
	Fork = fork;
	numMaxW = 0;
	assistant = p;
}
void Processor_FCFS::kill_sig(int timestep)
{

	sigkill s1;
	kill_queue.peek(s1);
	while (s1.time == timestep)
	{
		kill_queue.dequeue(s1);
		if (Runprocess)
		{
			if (s1.Pid == Runprocess->getPID())
			{
				assistant->move_to_trm(Runprocess);
				Runprocess = nullptr;
			}
		}
		LNode<Process*>* p1 = RDYlist.getbrain();
		if (!p1) // rdylist empty
		{
			return;
		}
		LNode<Process*>* p2 = RDYlist.getbrain()->getNext();



		while (!RDYlist.Is_brain(p2)) // transversing the ready list to see if any process has a sig kill
		{
			if (s1.Pid == p2->getItem()->getPID())
			{
				assistant->move_to_trm(p2->getItem());
				p1->setNext(p2->getNext());
				p2 = p2->getNext();
			}
			else
			{
				p1 = p1->getNext();
				p2 = p2->getNext();
			}

		}
		if (s1.Pid == p2->getItem()->getPID())
		{
			assistant->move_to_trm(p2->getItem());
			p1->setNext(p2->getNext());
			p2 = p2->getNext();
		}
		kill_queue.peek(s1);
	}
	// to see if there is any children that needs to be killed
	LNode<Process*>* p1 = RDYlist.getbrain();
	if (!p1) // rdylist empty
	{
		return;
	}
	LNode<Process*>* p2 = RDYlist.getbrain()->getNext();
	while (!RDYlist.Is_brain(p2)) // transversing the ready list to see if any process has been marked by oprh
	{
		if (p2->getItem()->orphan())
		{
			assistant->move_to_trm(p2->getItem());
			p1->setNext(p2->getNext());
			p2 = p2->getNext();
		}
		else
		{
			p1 = p1->getNext();
			p2 = p2->getNext();
		}

	}
	if (p2->getItem()->orphan())
	{
		assistant->move_to_trm(p2->getItem());
		p1->setNext(p2->getNext());
		p2 = p2->getNext();
	}

}
void Processor_FCFS::set_sigkill(LinkedQueue<sigkill>& kill_queue_out)
{
	kill_queue = kill_queue_out;
}
void Processor_FCFS::AddToList(Process* p)
{
	count++;
	state = true;
	FinishTime += p->getLeftCT();
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
	///*bool b = assistant->Migration_FCFS(Runprocess);
	//if (b)
	//{
	//	Runprocess=nullptr;
	//	ScheduleAlgo(assistant);
	//	return;
	//}*/
	// third  check fork
	/*assistant->(Runprocess); */
	// fourth excute
	Runprocess->decrementCT();
	TotalBusyTime++;
	if (Runprocess->getLeftCT() == 0)
	{
		assistant->move_to_trm(Runprocess);
		Runprocess = nullptr;
	}
	// fifth check for I_O request
	int ct = Runprocess->get_CT();
	int lct = Runprocess->getLeftCT();
	int ior = Runprocess->get_IO_R();
	if (ct - lct == ior)
	{
		assistant->RUNtoBLK(Runprocess);
	}
}
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

Process* Processor_FCFS::get_chosen_process()
{
	if (!Runprocess)
	{
		if (!RDYlist.isEmpty())
		{
			Process* choosen;
			RDYlist.peekfirst(choosen);
			return choosen;
		}
		else
		{
			return nullptr;
		}
	}
	return Runprocess;
}