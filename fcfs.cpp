#include <iostream>

using namespace std;

typedef struct data // defining a structure for holding the process details
{
	int at,bt,st,et;	//at-> arrival time, bt-> burst time, st-> starting time, et-> end time
}Data;

int main(int argc, char const *argv[])
{
	int n;
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;
	Data d[n];

	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process <arrival time, burst time > " << i+1<<": "; cin>>d[i].at>>d[i].bt;
	}
	cout << "\nprocess table:\n";   // showing all process details
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// Calculation starts here
	d[0].st = d[0].at; 
	d[0].et = d[0].at + d[0].bt;			// Calculation for the first process
	TAT = d[0].et - d[0].at;
	WT += (d[0].et - d[0].at) - d[0].bt;
	RT += d[0].st - d[0].at;

	cout << "\nGantt chart:\n";
	cout << "P"<<1<< "("<<d[0].st << "-"<<d[0].et<<") " ;   // printing the gantt chart  
	for(int i=1;i<n;i++){									// calculation for rest of the process
		if (d[i].at > d[i-1].et){					// if the arrival time of current process is greater than the end time of previous process
			d[i].st = d[i].at; 						// then starting time would be same as arrival time
			d[i].et = d[i].at + d[i].bt;			// and end time would be starting time added with burst time of curernt process
		}
		else {										// else 
			d[i].st = d[i-1].et; 					// starting time of current process would be same as end time of the previous process
			d[i].et = d[i].st + d[i].bt;			// and end time would be starting time added with burst time of curernt process
		}
		cout << "P"<<i+1<< "("<<d[i].st << "-"<<d[i].et<<") " ;
	
		TAT += d[i].et - d[i].at;				// Calculation for TTAT, TWT, TRT
		WT += (d[i].et - d[i].at) - d[i].bt;
		RT += d[i].st - d[i].at;
	}
	// after calculation 
	/*cout<< "After calc:"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<< " "<<d[i].st<< " "<<d[i].et<<endl;
	}*/

	cout << "\nResult:\n";
	cout<< "Total turn arround time: "<<TAT/n<<endl;
	cout<< "Total waiting time: "<<WT/n<<endl;
	cout<< "Total response time: "<<RT/n<<endl;

	return 0;
}