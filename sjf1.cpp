#include <iostream>
#include <algorithm>

using namespace std;

int visible[100];

typedef struct data
{
	int at,bt,st,et;
}Data;

Data d[100];

int searchMin(int ctr, int n){
	int min = 9999, j=-1;
	for (int i = 0; i < n; ++i)
	{
		if (min > d[i].bt && visible[i]!=1) { min = d[i].bt; j=i;}
	}
	return j;
}

int main(int argc, char const *argv[])
{
	int n,ctr=0, pctr=0;			// ctr = hold the pid of current process, pctr=hold the pid of previous process, Initially starts with 0
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;

	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process <arrival time, burst time > " << i+1<<": "; cin>>d[i].at>>d[i].bt;
	}

	cout << "\nprocess table:\n";   // showing all process details
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// calculation starts
	d[ctr].st = d[ctr].at; 					// calculation for the first process is done here
	d[ctr].et = d[ctr].at + d[ctr].bt;
	TAT += d[ctr].et - d[ctr].at;
	WT += (d[ctr].et - d[ctr].at) - d[ctr].bt;
	RT += d[ctr].st - d[ctr].at;
	visible[ctr] = 1;						// visible array is used to follow up the visited processes
	cout << "\nGantt chart:\n";
	cout << "P"<<ctr+1<< "("<<d[ctr].st << "-"<<d[ctr].et<<") " ;
	for(int i=1;i<n;i++){
		ctr = searchMin(pctr,n);			// search which process is having the min burst time among the available processes
		
		if (d[ctr].at > d[pctr].et){			// if the arrival time of current process is greater than the end time of previous process
			d[ctr].st = d[ctr].at; 				// then starting time would be same as arrival time
			d[ctr].et = d[ctr].at + d[ctr].bt;	// and end time would be starting time added with burst time of curernt process
		}
		else {									// else 
			d[ctr].st = d[pctr].et; 			// starting time of current process would be same as end time of the previous process
			d[ctr].et = d[ctr].st + d[ctr].bt;	// and end time would be starting time added with burst time of curernt process
		}
		visible[ctr] = 1;						// visible array is used to follow up the visited processes
		cout << "P"<<ctr+1<< "("<<d[ctr].st << "-"<<d[ctr].et<<") " ;	// printing gannt chart details

		TAT += d[ctr].et - d[ctr].at;
		WT += (d[ctr].et - d[ctr].at) - d[ctr].bt;	// Calculation for TTAT, TWT, TRT
		RT += d[ctr].st - d[ctr].at;
		pctr = ctr;		// assigning the current pid to previous pid at the end of execution
	}

	/*// after calculation 
	cout<< "After calc:"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<< " "<<d[i].st<< " "<<d[i].et<<endl;
	}*/

	cout << "\nResult:\n";
	cout<< "Total turn arround time: "<<TAT/n<<endl;
	cout<< "Total waiting time: "<<WT/n<<endl;
	cout<< "Total response time: "<<RT/n<<endl;

	return 0;
}