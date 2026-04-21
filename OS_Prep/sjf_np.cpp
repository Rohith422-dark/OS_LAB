#include<iostream>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(){
  int n; cout<<"Processes: "; cin>>n;

  int id[n],at[n],bt[n],st[n],ct[n],tat[n],wt[n];
  bool done[n]={};

  for(int i=0;i<n;i++){
    id[i]=i+1;
    cout<<"AT BT for P"<<i+1<<": ";
    cin>>at[i]>>bt[i];
  }

  int t=0,comp=0;
  float tw=0,tt=0;

  while(comp<n){
    int sel=-1,mn=INT_MAX;

    for(int i=0;i<n;i++){
      if(!done[i] && at[i]<=t && bt[i]<mn){
        mn=bt[i];
        sel=i;
      }
    }

    if(sel==-1){
      t++;
      continue;
    }

    st[sel]=t;
    ct[sel]=t+bt[sel];
    tat[sel]=ct[sel]-at[sel];
    wt[sel]=tat[sel]-bt[sel];

    t=ct[sel];
    done[sel]=true;
    comp++;

    tw+=wt[sel];
    tt+=tat[sel];
  }

  cout<<"\nPID\tAT\tBT\tST\tCT\tTAT\tWT\n";
  for(int i=0;i<n;i++){
    cout<<id[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"
        <<st[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
  }

  cout<<"Avg WT="<<tw/n<<" Avg TAT="<<tt/n<<"\n";

  // ✅ Compute max completion time
  int mx=0;
  for(int i=0;i<n;i++)
    mx=max(mx,ct[i]);

  // ✅ Gantt Chart Code
  ofstream g("g.gp");

  g<<"set title 'SJF-NP Gantt'\n";
  g<<"set xlabel 'Time'\n";
  g<<"set yrange [0:"<<n+1<<"]\n";
  g<<"set xrange [0:"<<mx+1<<"]\n";

  g<<"set ytics (";
  for(int i=0;i<n;i++){
    g<<"'P"<<id[i]<<"' "<<i+1;
    if(i<n-1) g<<",";
  }
  g<<")\n";

  for(int i=0;i<n;i++){
    g<<"set obj rect from "<<st[i]<<","<<i+0.7
     <<" to "<<ct[i]<<","<<i+1.3
     <<" fc rgb 'skyblue'\n";
  }

  g<<"plot 0 notitle\npause -1\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}