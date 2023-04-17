#include "UI.h"

UI::UI()
{
}

void UI::PrintOutput(LinkedQueue<Process*>& NEW_LIST, LinkedQueue<Process*>& BLK_LIST, LinkedList<Process*>& TRM_LIST, LinkedList<Processor*>& Processors,
	int timestep, int Processes_no, int Term_no)
{
	cout << "Current Timestep:" << timestep<<endl;
	cout << "---------------" << "	RDY processes	" << "---------------"<<endl;
	Processors.PrintList();
	cout << "---------------" << "	BLK processes	" << "---------------" << endl;
	cout << BLK_LIST.Get_Count() << " BLK: ";
	BLK_LIST.PrintList();
	cout << "---------------" << "	RUN processes	" << "---------------" << endl;
	/*cout << RUN_List.count << "RUN: " << RUN_List.PrintList();*/
	cout << "---------------" << "	TRM processes	" << "---------------" << endl;
	cout << TRM_LIST.getcount() << "TRM: ";
	TRM_LIST.PrintList();
	cout << endl;
	cout << "PRESS ANY KEY TO MOVE TO THE NEXT STEP !";
	char x;
	cin >> x;
}
