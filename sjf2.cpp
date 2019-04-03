#include <iostream>
#include <algorithm>

using namespace std;

typedef struct data
{
	int at,bt,st,et;
}Data;

Data d[100];
bool completed[100], visited[100];			// completed array is used to indicate the completed process
int n,timeC=-1,newPr=-1,comPr=0, Bt[100];	// newPr= hold the pid of the process that will arrive next, comPr=hold the number of completed process 

int getMin() {
	int min=9999,i,j=-1;
	for (i = 0; i < n; ++i)
	{
		if ( timeC>=d[i].at){
			if (!completed[i]){
				if (min>Bt[i]) { j=i; min=Bt[i];}
			}
		} else { break;}		
	}
	if (newPr<i) { newPr=i;}
	return j;
}

int main()
{
	int prAv=-1;
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;

	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process <arrival time, burst time > " << i+1<<": "; cin>>d[i].at>>d[i].bt; Bt[i]=d[i].bt;
	}

	cout << "\nProcess table"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " -> "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// calculation starts
	int p=0,nextC=-1;	// nextC = hold the time the current process can execute before further checking for pre-emtion 
	timeC=d[p].at;
	cout << "\nGantt chart:\n";
	while (comPr!=n) {			// while the number of completed processes is not equals to total number of processes
		p = getMin(); 			// search which process is having the min burst time among the available processes 
		if (!(p+1)) { timeC=d[newPr].at; p=getMin();}	// when the search is failed, p value is -1
		//cout<< "Min: p"<<p+1<<endl;
		cout << "P"<<p+1<< "("<<timeC << "-";
		if (visited[p]==0) { d[p].st = timeC; visited[p]=1;}	// when a process is executing first time, starting time is assigned here
		if (newPr!=n) { 		// if next process is not equals to the last process
			nextC = d[newPr].at - timeC; 
			if (nextC >= Bt[p]) { 
				timeC+=Bt[p]; 
				d[p].et = timeC; 
				Bt[p]=0; 
				completed[p]=1; comPr++;
			}
			else { timeC+=nextC; Bt[p]-=nextC;}
		} else {
			timeC+=Bt[p]; Bt[p]=0; completed[p]=1; comPr++; d[p].et=timeC;
		}
		cout << timeC << ") ";
		if (completed[p]) {
			TAT += d[p].et - d[p].at;
			WT += (d[p].et - d[p].at) - d[p].bt;
			RT += d[p].st - d[p].at;

		} 
	}
	/*
	cout<< "After:"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<<"->"<<d[i].st<<" "<<d[i].et<<" "<< Bt[i]<<endl;
	}*/

	cout << "\nResult:\n";
	cout<< "Total turn arround time: "<<TAT/n<<endl;
	cout<< "Total waiting time: "<<WT/n<<endl;
	cout<< "Total response time: "<<RT/n<<endl;


	return 0;
}