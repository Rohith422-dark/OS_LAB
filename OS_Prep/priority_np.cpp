#include<iostream>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(){
  int n; cout<<"Processes: "; cin>>n;

  int id[n],at[n],bt[n],pr[n],st[n],ct[n],tat[n],wt[n];
  bool done[n]={};

  for(int i=0;i<n;i++){
    id[i]=i+1;
    cout<<"AT BT Priority for P"<<i+1<<": ";
    cin>>at[i]>>bt[i]>>pr[i];
  }

  int t=0,comp=0;
  float tw=0,tt=0;

  // ✅ Gantt arrays
  int gP[100], gS[100], gE[100], k=0;

  while(comp<n){
    int sel=-1,bp=INT_MAX;

    for(int i=0;i<n;i++){
      if(!done[i] && at[i]<=t && pr[i]<bp){
        bp=pr[i];
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

    // ✅ Store for Gantt
    gP[k]=sel;
    gS[k]=t;
    gE[k]=ct[sel];
    k++;

    t=ct[sel];
    done[sel]=true;
    comp++;

    tw+=wt[sel];
    tt+=tat[sel];
  }

  cout<<"\nPID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\n";
  for(int i=0;i<n;i++){
    cout<<id[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<pr[i]<<"\t"
        <<st[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
  }

  cout<<"Avg WT="<<tw/n<<" Avg TAT="<<tt/n<<"\n";

  // ✅ Gantt Chart Code
  ofstream g("g.gp");

  g<<"set title 'Priority-NP Gantt'\n";
  g<<"set xlabel 'Time'\n";
  g<<"set yrange [0:"<<n+1<<"]\n";
  g<<"set xrange [0:"<<t+1<<"]\n";

  g<<"set ytics (";
  for(int i=0;i<n;i++){
    g<<"'P"<<id[i]<<"' "<<i+1;
    if(i<n-1) g<<",";
  }
  g<<")\n";

  for(int i=0;i<k;i++){
    g<<"set obj rect from "<<gS[i]<<","<<gP[i]+0.6
     <<" to "<<gE[i]<<","<<gP[i]+1.4
     <<" fc rgb 'light-green'\n";
  }

  g<<"plot 0 notitle\npause -1\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}