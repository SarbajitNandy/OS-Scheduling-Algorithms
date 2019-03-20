#include <iostream>
#include <algorithm>

using namespace std;

int visible[100];

typedef struct data
{
	int at,bt,st,et;
}Data;

Data d[100];

bool compare(Data a, Data b){
	return (a.at < b.at);	
}

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
	int n,ctr, pctr;
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;

	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process " << i+1<<": "; cin>>d[i].at>>d[i].bt;
	}

	sort(d, d+n, compare );

	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// calculation starts
	pctr = 0; ctr = 0;
	d[ctr].st = d[ctr].at; 
	d[ctr].et = d[ctr].at + d[ctr].bt;
	TAT += d[ctr].et - d[ctr].at;
	WT += (d[ctr].et - d[ctr].at) - d[ctr].bt;
	RT += d[ctr].st - d[ctr].at;
	visible[ctr] = 1;
	for(int i=1;i<n;i++){
		ctr = searchMin(pctr,n);
		if (d[ctr].at > d[pctr].et){
			d[ctr].st = d[ctr].at; 
			d[ctr].et = d[ctr].at + d[ctr].bt;
		}
		else {
			d[ctr].st = d[pctr].et; 
			d[ctr].et = d[ctr].st + d[ctr].bt;
		}
		visible[ctr] = 1;
		TAT += d[ctr].et - d[ctr].at;
		WT += (d[ctr].et - d[ctr].at) - d[ctr].bt;
		RT += d[ctr].st - d[ctr].at;
		pctr = ctr;
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