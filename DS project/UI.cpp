#include"UI.h"
#include<Windows.h>
UI::UI()
{
}

void UI::PrintOutput(LinkedList<Process*>& RUN_List, LinkedQueue<Process*>& NEW_LIST, LinkedQueue<Process*>& BLK_LIST, LinkedList<Process*>& TRM_LIST, LinkedList<Processor*>& Processors,
	int timestep, int Processes_no, int Term_no)
{
	if (Mode != 2) // not silent mode
	{
		cout << "\nCurrent Timestep:" << timestep << endl;
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

		if (Mode == 0) // interactive mode
		{
			char x;
			cin >> x;
		}
		else // step by step mode
		{
			Sleep(1);
		}
	}
}

UI::~UI()
{
	if (Mode == 2)
	{
		cout << "Simulation ends, Output file created";
	}
}
void UI::setmode()
{
	cout << "please enter the mode of the interface:\n";
	cout << "0:interactive mode\n";
	cout << "1:step by step mode\n";
	cout << "2:silent mode\n";
	int x = 0;   // for testing
	cin >> x;
	Mode = x;
	if (Mode == 2)
	{
		cout << "Silent Mode........... Simulation Starts...\n";
	}
}
ostream& operator << (ostream& out, Process* P)
{
	cout << P->PID;
	if (P->Processor_id != -1)
	{
		cout << "(P" << P->Processor_id << ")";
	}
	cout << ",";
	return out;
}
ostream& operator << (ostream& out, Processor* P)
{
	cout << "Processor " << P->ID << " [" << P->Name << "]: ";
	cout << P->GetRdyCount() << " ";
	cout << "RDY: ";
	P->print();
	cout << endl;
	return out;
}