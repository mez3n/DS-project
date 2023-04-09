#include "Stream.h"

Stream::Stream()
{
	InputFile = new ifstream("InputFile.txt");
}

Stream::~Stream()
{
	delete InputFile;
	delete OutputFile;
}

void Stream::LoadInputs()
{
	// all of this is string you should use stoi()

	string FCFS_no, SJF_no, RR_no;  //number of each type of processor
	string timeslice_RR;            // time slice for round robin processor
	string RTF, MaxW, STL, Fork_prop;   // data of processors //overheating number should be added
	*InputFile >> FCFS_no >> SJF_no >> RR_no;
	*InputFile >> RTF >> MaxW >> STL >> Fork_prop;  // EDF should be added
	// constructor of processor class should be called here 


	string processes_no;
	*InputFile >> processes_no;
	string pid, at, rt, ct, tt, no_IO, IO; //each process specifications 
	for (int pid = 0; pid < stoi(processes_no); pid++)
	{
		*InputFile >> no_IO >> at >> rt >> ct >> tt >> IO;
		int* IO_R = new int[stoi(processes_no)] {0};
		int* IO_D = new int[stoi(processes_no)] {0};
		for (int i = 0; i < IO.length(); i++)  //processing the IO string 
		{
			if (isdigit(IO[i]))
			{
				if (IO[i - 1]=='(')
				{
					while (isdigit(IO[i]))
					{
						IO_R[pid] = IO_R[pid] * 10 + IO[i];
						i++;
					}
				}
				else
				{
					while (isdigit(IO[i]))
					{
						IO_D[pid] = IO_D[pid] * 10 + IO[i];
						i++;
					}
				}
			}
			else
			{
				continue;
			}
		}

		//sigkill Times
		string kill_id, kill_time;
		int* kill_time_arr = new int [stoi(processes_no)] {-1};
		while (!InputFile->eof())
		{
			*InputFile >> kill_time >> kill_id;
			kill_time_arr[stoi(kill_id)] = stoi(kill_time);
		}  
		// finished reading all inputs




		// settle on a way to make the processes list

		

		




	}


}
