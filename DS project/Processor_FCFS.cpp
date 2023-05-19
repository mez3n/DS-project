#include"Processor_FCFS.h"
#include"scheduler.h"
struct sigkill;
Processor_FCFS::Processor_FCFS(int N, int id, string name, scheduler* p) :Processor(N, id, name, p)
{
	assistant = p;
}
void Processor_FCFS::kill_sig(int timestep)
{

	sigkill s1;
	kill_queue.peek(s1);
	while (s1.time == timestep)
	{
		if (!kill_queue.dequeue(s1))
		{
			break;
		}
		
		if (Runprocess)
		{
			if (s1.Pid == Runprocess->getPID())
			{
				assistant->move_to_trm(Runprocess);
				removerunprocess();
				
			}
		}
		LNode<Process*>* p1 = RDYlist.getbrain();
		if (!p1) // rdylist empty
		{
			kill_queue.peek(s1);
			continue;
		}
		LNode<Process*>* p2 = RDYlist.getbrain()->getNext();


		p1->getItem()->set_WT(p1->getItem()->get_WT() + 1);  // updating WT for first process in RDY list
		while (p2) // transversing the ready list to see if any process has a sig kill
		{
			p2->getItem()->set_WT(p2->getItem()->get_WT() + 1); //updating WT for all process in RDY list
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
		if (s1.Pid == p1->getItem()->getPID())
		{
			assistant->move_to_trm(p1->getItem());
			p1 = p1->getNext();
		}
		kill_queue.peek(s1);
	}
	// to see if there is any children that needs to be killed

	
	if (Runprocess)  // to see if running process is orphan
	{
		if (Runprocess->orphan())
		{
			assistant->move_to_trm(Runprocess);
			removerunprocess();
		}
	}

	LNode<Process*>* p1 = RDYlist.getbrain();
	if (!p1) // rdylist empty
	{
		return;
	}
	LNode<Process*>* p2 = RDYlist.getbrain()->getNext();
	while (p2) // transversing the ready list to see if any process has been marked by oprh
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
	p1 = RDYlist.getbrain();
	if (!p1) // rdylist empty
	{
		return;
	}
	if (p1->getItem()->orphan())
	{
		assistant->move_to_trm(p1->getItem());
		p1 = p1->getNext();
	}

}
void Processor_FCFS::set_sigkill(LinkedQueue<sigkill> & kill_queue_out)
{
	kill_queue = kill_queue_out;
}
void Processor_FCFS::AddToList(Process* p)
{
	count++;
	FinishTime += p->getLeftCT();
	RDYlist.InsertEnd(p);
}
void Processor_FCFS::print()
{
	RDYlist.PrintList();
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

void Processor_FCFS::ScheduleAlgo()
{
	if (!Runprocess)
	{
		if (!RDYlist.isEmpty())
		{
			RDYlist.DeleteFirst(Runprocess);
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
Process* Processor_FCFS::get_first_process()
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
void Processor_FCFS::overheat_check()// need modification to handel if process is forked and this is the only FCFS
{
	if (leftn > 0)
	{
		leftn--;
	}
	else
	{
		srand(time(0));
		int  r = 1 + (rand() % 100);
		if (r <= 5 && r > 0)
		{
			FinishTime = 0;
			leftn = n;
			if (Runprocess)
			{
				if (Runprocess->is_forked()) 
				{
					assistant->AddToShortestFCFS(Runprocess);
				}
				else 
				{
					assistant->Add_To_Shortest_RDY(Runprocess);
				}
				Runprocess = nullptr;
				state = false;
			}
			Process* p;
			while (!RDYlist.isEmpty())// modified (not added)
			{
				RDYlist.DeleteFirst(p);
				if (p->is_forked())
				{
					assistant->AddToShortestFCFS(p);
				}
				else
				{
					assistant->Add_To_Shortest_RDY(p);
				}
			}
		}
	}
}
void Processor_FCFS::switch_processes(Processor*& p)
{
	// check implement please (a function that take take the first process in (this) and give it to p)
	Process* px;
	RDYlist.DeleteFirst(px);
	count--;
	FinishTime -= px->getLeftCT();
	p->AddToList(px);
}
