#include<iostream>
#include<queue>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(){
  int n,tq;
  cout<<"Processes & "<<"Processes Quantum: ";
  cin>>n>>tq;

  int id[n],at[n],bt[n],rem[n],ct[n],tat[n],wt[n];

  for(int i=0;i<n;i++){
    id[i]=i+1;
    cout<<"AT BT for P"<<i+1<<": ";
    cin>>at[i]>>bt[i];
    rem[i]=bt[i];
  }

  struct G{ int idx,s,e; } g[500]; // store index, not pid
  int gIdx=0;

  queue<int> q;
  bool inQ[n]={};

  int t=0,comp=0;

  while(comp<n){

    for(int i=0;i<n;i++){
      if(at[i]<=t && !inQ[i] && rem[i]>0){
        q.push(i);
        inQ[i]=true;
      }
    }

    if(q.empty()){
      t++;
      continue;
    }

    int idx=q.front();
    q.pop();

    int ex=min(tq,rem[idx]);

    // ✅ Store Gantt segment
    g[gIdx]={idx,t,t+ex};
    gIdx++;

    t+=ex;
    rem[idx]-=ex;

    for(int i=0;i<n;i++){
      if(at[i]<=t && !inQ[i] && rem[i]>0){
        q.push(i);
        inQ[i]=true;
      }
    }

    if(rem[idx]>0){
      q.push(idx);
    } else {
      ct[idx]=t;
      comp++;
    }
  }

  float tw=0,tt=0;

  for(int i=0;i<n;i++){
    tat[i]=ct[i]-at[i];
    wt[i]=tat[i]-bt[i];
    tw+=wt[i];
    tt+=tat[i];
  }

  cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";
  for(int i=0;i<n;i++){
    cout<<id[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"
        <<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
  }

  cout<<"Avg WT="<<tw/n<<" Avg TAT="<<tt/n<<"\n";

  // ✅ Gantt Chart Code
  ofstream gp("g.gp");

  gp<<"set title 'Round Robin Gantt'\n";
  gp<<"set xlabel 'Time'\n";
  gp<<"set yrange [0:"<<n+1<<"]\n";
  gp<<"set xrange [0:"<<t+1<<"]\n";

  gp<<"set ytics (";
  for(int i=0;i<n;i++){
    gp<<"'P"<<id[i]<<"' "<<i+1;
    if(i<n-1) gp<<",";
  }
  gp<<")\n";

  for(int i=0;i<gIdx;i++){
    int y=g[i].idx+1;

    gp<<"set obj rect from "<<g[i].s<<","<<y+0.6
      <<" to "<<g[i].e<<","<<y+1.4
      <<" fc rgb 'violet'\n";
  }

  gp<<"plot 0 notitle\npause -1\n";
  gp.close();

  system("gnuplot g.gp");

  return 0;
}