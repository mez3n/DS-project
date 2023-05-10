
#include <Windows.h>
#
#include"UI.h"
#include<iostream>
using namespace std;
UI::UI()
{
}

void UI::set_mode()
{
	cout << "Please enter the operation mode:\n";
	cout << "Interactive mode is 0 \n";
	cout << "step-by-step mode mode is 1 \n";
	cout << "silent mode is 2 \n";
	cin >> mode;
	cout << "\n==============================================================================================================\n";
}

void UI::PrintOutput(LinkedList<Process*>& RUN_List,LinkedQueue<Process*>& NEW_LIST, LinkedQueue<Process*>& BLK_LIST, LinkedList<Process*>& TRM_LIST, LinkedList<Processor*>& Processors,
	int timestep, int Processes_no, int Term_no)
{
	if (mode == 0|| mode==1)
	{
		cout << "Current Timestep:" << timestep << endl;
		cout << "---------------" << "	RDY processes	" << "---------------" << endl;
		cout << " ";
		Processors.PrintList();
		cout << "---------------" << "	BLK processes	" << "---------------" << endl;
		cout << BLK_LIST.Get_Count() << " BLK: ";
		BLK_LIST.PrintList();
		cout << endl;
		cout << "---------------" << "	RUN processes	" << "---------------" << endl;
		cout << RUN_List.getcount() << " RUN: ";
		RUN_List.PrintList();
		cout << "---------------" << "	TRM processes	" << "---------------" << endl;
		cout << TRM_LIST.getcount() << " TRM: ";
		TRM_LIST.PrintList();
		cout << "PRESS ANY KEY TO MOVE TO THE NEXT STEP !";
		cout << endl;
		cout << "==================================================================";
		if (mode == 0)
		{
			char x;
			cin >> x;
		}
		else
		{
			Sleep(1000);
			
		}
	}
	else if (mode == 2)
	{
		cout << "Silent Mode...............    simulation starts. . .\n";
		cout << "Simulation ends, output file created";
	}
	
}

UI::~UI()
{
}
ostream& operator << (ostream& out, Process* P)
{
	cout <<P->PID;
	if (P->Processor_id != -1)
	{
		cout << "(P" << P->Processor_id<<")";
	}
	cout << ",";
	return out;
}
ostream& operator << (ostream& out, Processor* P)
{
	cout << "Processor " << P->ID << " [" << P->Name << "]: ";
	cout << P->GetRdyCount()<<" ";
	cout<< "RDY: ";
	P->print();
	cout << endl;
	return out;
}