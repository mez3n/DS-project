#include"scheduler.h"
#ifndef UI_
#define UI_
class UI
{
private:
	int Mode; // mode set at the start of the program, 0: interactive mode, 1:step by step mode, 2:silent mode
public:
	UI();

	void PrintOutput(LinkedList<Process*>& RUN_List,LinkedQueue<Process*>& NEW_LIST, LinkedQueue<Process*>& BLK_LIST, LinkedList<Process*>& TRM_LIST, LinkedList<Processor*>& Processors,
		int timestep, int Processes_no, int Term_no); // print all function called by scheduler at the end of each time step
	~UI();
	void setmode();
	
};
#endif


ostream& operator << (ostream& out, Process* P);

ostream& operator << (ostream& out, Processor* P);

