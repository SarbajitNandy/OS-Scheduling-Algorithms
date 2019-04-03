#include <iostream>

using namespace std;

typedef struct data
{
	int at,bt,st,et;
}Data;

Data d[100];	// Declaring the mem space
int visible[100];	// Declaring visible field
int queue[100];		// Declaring queue
int n, timeq,front=-1, rear=-1;

// Building the queue operations
int isEmpty(){
	return (front==rear && front==-1);
}

int enqueue(int p){				// circular queue has been used
	if (front == (rear+1)%n){
		return 0;
	} else if ( rear==front && front==-1) {
		front=rear=0; queue[rear]=p;
	} else {
		rear = (rear+1)%n; queue[rear]=p;
	}
	return 1;
}

int dequeue() {
	int p=-1;
	if ( isEmpty()){
		return -1;
	}
	else if (front==rear && rear!=-1) {
		p=queue[front];	front=rear=-1;
	} else {
		p=queue[front]; front=(front+1)%n;
	}
	return p;
}

int main()
{
	int timeC=0;
	float TAT=0,WT=0,RT=0;
	
	cout<< "Enter the no of process: "; cin>>n;
	int BT[n];
	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process <arrival time, burst time > " << i+1<<": "; cin>>d[i].at>>d[i].bt; BT[i]=d[i].bt;
	}
	cout<< "Enter time quanta: ";
	cin>>timeq;

	// printing the data
	for(int i=0; i<n;i++){
		cout<<i+1<< " " <<d[i].at<<" "<<d[i].bt<<endl;
	}

	// calculation start here
	int j=1,p; bool en;
	timeC = d[0].at;
	enqueue(0);
	cout << "\nGantt chart:\n";

	while (!isEmpty() || j!=n) {
		
		p = dequeue();
		if (p==-1) { p=j, j++; timeC=d[p].at;}
		cout << "P"<<p+1<< "("<<timeC << "-";
		if (visible[p]==0) { d[p].st = timeC; visible[p]=1;}
		if (BT[p] <= timeq) {
			timeC+=BT[p]; d[p].et = timeC; BT[p]=0;	en=0;
		} else {
			timeC+=timeq; BT[p]-=timeq; en=1;
		}
		for(;j<n;j++){
			if (d[j].at <= timeC) { enqueue(j);}
			else { break;}
		}
		cout << timeC << ") ";
		if (en) { enqueue(p);}
		
	}
/*
	cout<< endl << "Ultimate result: "<< endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " " <<d[i].at<<" "<<d[i].bt<< " "<<d[i].st<< " "<<d[i].et<<endl;
	}
*/
	// calculation for time
	for(int i=0; i<n;i++){
		TAT += d[i].et - d[i].at;
		WT += (d[i].et - d[i].at) - d[i].bt;
		RT += d[i].st - d[i].at;
	}

	cout << "\nResult:\n";
	cout<< "Total turn arround time: "<<TAT/n<<endl;
	cout<< "Total waiting time: "<<WT/n<<endl;
	cout<< "Total response time: "<<RT/n<<endl;

	return 0;

}