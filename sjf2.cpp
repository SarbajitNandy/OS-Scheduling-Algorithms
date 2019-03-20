#include <iostream>
#include <algorithm>

using namespace std;

typedef struct data
{
	int at,bt,st,et;
}Data;

Data d[100];
bool completed[100], visited[100];
int n,timeC=-1,newPr=-1,comPr=0;

int getMin() {
	int min=9999,i,j=-1;
	for (i = 0; i < n; ++i)
	{
		if ( timeC>=d[i].at){
			if (!completed[i]){
				if (min>d[i].bt) { j=i; min=d[i].at;}
			}
		} else { break;}		
	}
	if (newPr!=n) { newPr=i;}
	return j;
}

int main()
{
	int prAv=-1;
	float TAT=0,WT=0,RT=0;
	cout<< "Enter the no of process: "; cin>>n;

	// filling the data
	for(int i=0; i<n;i++){
		cout<< "Enter data for process " << i+1<<": "; cin>>d[i].at>>d[i].bt;
	}

	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<endl;
	}

	// calculation starts
	int p=0,nextC=-1;
	timeC=d[p].at;
	while (comPr!=n) {
		p = getMin(); 
		if (p+1) { timeC=d[newPr].at; p=getMin();}
		cout<< "Min: p"<<p+1<<endl;
		if (visited[p]==0) { d[p].st = timeC; visited[p]=1;}
		if (newPr!=n) { 
			nextC = d[newPr].at - timeC; cout<<"---p"<<p+1 <<"nextPr:"<<newPr+1<<endl;
			if (nextC >= d[p].bt) { timeC+=d[p].bt; d[p].et = timeC; d[p].bt=0; completed[p]=1; comPr++;}
			else { timeC+=nextC; d[p].bt-=nextC;}
			if (newPr==n-1) { newPr++;}
		} else {
			timeC+=d[p].bt; d[p].bt=0; completed[p]=1; comPr++; d[p].et=timeC;
		}
	}
	cout<< "After:"<<endl;
	for(int i=0; i<n;i++){
		cout<<i+1<< " "<<d[i].at<<" "<<d[i].bt<<" "<<d[i].st<<" "<<d[i].et<<endl;
	}



	return 0;
}