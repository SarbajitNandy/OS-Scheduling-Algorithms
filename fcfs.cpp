#include <iostream>
#include <algorithm>
using namespace std;

typedef struct data
{
	int at,bt,st,et;
}Data;

bool compare(Data a, Data b){
	return (a.at < b.at);	
}
int main(int argc, char const *argv[])
{
	int n;
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;
	Data d[n];
	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process " << i+1<<": "; cin>>d[i].at>>d[i].bt;
	}
	sort(d, d+n, compare );
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// Calculation starts here
	d[0].st = d[0].at; 
	d[0].et = d[0].at + d[0].bt;
	TAT = d[0].et - d[0].at;
	WT += (d[0].et - d[0].at) - d[0].bt;
	RT += d[0].st - d[0].at;
	for(int i=1;i<n;i++){
		if (d[i].at > d[i-1].et){
			d[i].st = d[i].at; 
			d[i].et = d[i].at + d[i].bt;
		}
		else {
			d[i].st = d[i-1].et; 
			d[i].et = d[i].st + d[i].bt;
		}
		TAT += d[i].et - d[i].at;
		WT += (d[i].et - d[i].at) - d[i].bt;
		RT += d[i].st - d[i].at;
	}
	// after calculation 
	cout<< "After calc:"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<< " "<<d[i].st<< " "<<d[i].et<<endl;
	}

	cout<< "TTAT: "<<TAT/n<<endl;
	cout<< "WT: "<<WT/n<<endl;
	cout<< "RT: "<<RT/n<<endl;

	return 0;
}