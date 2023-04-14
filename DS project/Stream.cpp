#include "Stream.h"

Stream::Stream()
{
	InputFile = new ifstream("InputFile.txt");
}

Stream::~Stream()
{
	delete InputFile;
	delete OutputFile;
	string process_no;
	*InputFile >> process_no;
	processes_no = stoi(process_no);
	string no_rr, no_fcfs, no_sjf;
	*InputFile >> no_fcfs, no_sjf, no_rr;
	FCFS_no = stoi(no_fcfs);
	SJF_no = stoi(no_sjf);
	RR_no = stoi(no_rr);
}

void Stream::LoadProcesses(int pid ,int no_IO, int at, int rt, int ct,int*& IO_r, int*& IO_d) 
{
	// all of this is string you should use stoi()
	// any string has S before its name

	// constructor of processor class should be called here 
	string Spid, Sat, Srt, Sct, Stt, Sno_IO, SIO; //each process specifications 
	*InputFile >> Sat>> Spid >> Sct >>Sno_IO >> SIO;
	no_IO = stoi(Sat);
	at = stoi(Sat);
	rt = stoi(Srt);
	ct = stoi(Sct);
	no_IO=stoi(Sno_IO);
	pid = stoi(Spid);
	int* IO_R = new int[no_IO] {0};
	int* IO_D = new int[no_IO] {0};
	int j = 0;
	for (int i = 0; i < SIO.length(); i++)  //processing the IO string 
	{
		if (isdigit(SIO[i]))
		{
			if (SIO[i - 1] == '(')
			{
				while (isdigit(SIO[i]))
				{
					IO_R[j] = IO_R[j] * 10 + SIO[i];
					i++;
				}

			}
			else
			{
				while (isdigit(SIO[i]))
				{
					IO_D[j] = IO_D[j] * 10 + SIO[i];
					i++;
				}
				j++;
			}
		}
		else
		{
			continue;
		}
	}
	IO_d = IO_D;
	IO_r = IO_R;


	// finished reading all inputs


}

void Stream::get_counts(int& no_fcfs, int& no_sjf, int& no_rr, int& process_no)
{
	no_fcfs = FCFS_no;
	no_sjf = SJF_no;
	no_rr = RR_no;
	process_no = processes_no;
}

void Stream::load_sigkill(int* &kill_arr)
{
	//sigkill Times


	string kill_id, kill_time;
	int* kill_time_arr = new int [processes_no] {-1};  // each index in the array is a proccesor id if it is not -1 then the process should be killed at the time specified
	while (!InputFile->eof())
	{
		*InputFile >> kill_time >> kill_id;
		kill_time_arr[stoi(kill_id)] = stoi(kill_time);
	}
	kill_arr = kill_time_arr;
}
