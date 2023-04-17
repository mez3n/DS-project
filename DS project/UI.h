#include<iostream>
#include"process.h"
#include"processor.h"
#include"scheduler.h"
using namespace std;
#ifndef UI_
#define UI_


ostream& operator << (ostream& out, Process* P)
{
	cout << P->PID << " ";
	return out;
}
ostream& operator << (ostream& out, Processor* P)
{
	cout << "Processor " << "processor ID (edit)" << " [" << " type (edit) " << "]:  " << "RDY: ";
	P->print();
	return out;
}
class UI
{
public:
	void PrintOutput(LinkedQueue<Process*> &NEW_LIST,LinkedQueue<Process*>& BLK_LIST,LinkedList<Process*> &TRM_LIST, LinkedList<Processor*>& Processors,
		int timestep, int Processes_no,int Term_no);
};
#endif















