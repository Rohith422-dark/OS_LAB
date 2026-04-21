#include<iostream>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(){
  int n; cout<<"Processes: "; cin>>n;

  int id[n],at[n],bt[n],rem[n],ct[n],tat[n],wt[n];

  for(int i=0;i<n;i++){
    id[i]=i+1;
    cout<<"AT BT for P"<<i+1<<": ";
    cin>>at[i]>>bt[i];
    rem[i]=bt[i];
  }

  int t=0,comp=0,prev=-1;
  float tw=0,tt=0;

  // ✅ Gantt tracking arrays
  int gP[1000], gT[1001], gIdx=0;

  while(comp<n){
    int sel=-1,mn=INT_MAX;

    for(int i=0;i<n;i++){
      if(rem[i]>0 && at[i]<=t && rem[i]<mn){
        mn=rem[i];
        sel=i;
      }
    }

    if(sel==-1){
      t++;
      continue;
    }

    // Record change in process
    if(prev!=sel){
      gP[gIdx]=sel;
      gT[gIdx]=t;
      gIdx++;
      prev=sel;
    }

    rem[sel]--;
    t++;

    if(rem[sel]==0){
      ct[sel]=t;
      tat[sel]=ct[sel]-at[sel];
      wt[sel]=tat[sel]-bt[sel];

      tw+=wt[sel];
      tt+=tat[sel];
      comp++;
    }
  }

  gT[gIdx]=t;

  cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";
  for(int i=0;i<n;i++){
    cout<<id[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"
        <<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
  }

  cout<<"Avg WT="<<tw/n<<" Avg TAT="<<tt/n<<"\n";

  // ✅ Gantt Chart Code
  ofstream g("g.gp");

  g<<"set title 'SRTF Gantt'\n";
  g<<"set xlabel 'Time'\n";
  g<<"set yrange [0:"<<n+1<<"]\n";
  g<<"set xrange [0:"<<t+1<<"]\n";

  g<<"set ytics (";
  for(int i=0;i<n;i++){
    g<<"'P"<<id[i]<<"' "<<i+1;
    if(i<n-1) g<<",";
  }
  g<<")\n";

  int s=gT[0], pr=gP[0];

  for(int i=1;i<=gIdx;i++){
    if(i==gIdx || gP[i]!=pr){
      int y=pr+1;

      g<<"set obj rect from "<<s<<","<<y-0.3
       <<" to "<<gT[i]<<","<<y+0.3
       <<" fc rgb 'skyblue'\n";

      if(i<gIdx){
        s=gT[i];
        pr=gP[i];
      }
    }
  }

  g<<"plot 0 notitle\npause -1\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}