#include<iostream>
#include<algorithm>
#include<fstream>
#include<cstdlib>
using namespace std;

struct P{ int id,at,bt,st,ct,tat,wt; };

bool cmpAT(P a,P b){ return a.at<b.at; }

int main(){
  int n; cout<<"Processes: "; cin>>n;

  P p[n];

  for(int i=0;i<n;i++){
    p[i].id=i+1;
    cout<<"AT BT for P"<<i+1<<": ";
    cin>>p[i].at>>p[i].bt;
  }

  sort(p,p+n,cmpAT);

  int t=0; float tw=0,tt=0;

  for(int i=0;i<n;i++){
    if(t<p[i].at) t=p[i].at;

    p[i].st=t;
    p[i].ct=t+p[i].bt;
    p[i].tat=p[i].ct-p[i].at;
    p[i].wt=p[i].tat-p[i].bt;

    t=p[i].ct;
    tw+=p[i].wt;
    tt+=p[i].tat;
  }

  cout<<"\nPID\tAT\tBT\tST\tCT\tTAT\tWT\n";
  for(int i=0;i<n;i++)
    cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"
        <<p[i].st<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\n";

  cout<<"Avg WT="<<tw/n<<" Avg TAT="<<tt/n<<"\n";

  int maxCT=p[n-1].ct;

  // ✅ Gantt Chart Code
  ofstream g("g.gp");

  g<<"set title 'FCFS Gantt'\n";
  g<<"set xlabel 'Time'\n";
  g<<"set yrange [0:"<<n+1<<"]\n";
  g<<"set xrange [0:"<<maxCT+1<<"]\n";

  g<<"set ytics (";
  for(int i=0;i<n;i++){
    g<<"'P"<<p[i].id<<"' "<<i+1;
    if(i<n-1) g<<",";
  }
  g<<")\n";

  for(int i=0;i<n;i++){
    g<<"set obj rect from "<<p[i].st<<","<<i+0.7
     <<" to "<<p[i].ct<<","<<i+1.3
     <<" fc rgb 'skyblue'\n";
  }

  g<<"plot 0 notitle\npause -1\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}