#include<iostream>
#include<climits>
using namespace std;
int frames,n,pages[100];
bool inFrame(int mem[],int p){ for(int i=0;i<frames;i++) if(mem[i]==p) return true; return false; }
void fifo(){
  int mem[frames],front=0,f=0,h=0;
  fill(mem,mem+frames,-1);
  for(int i=0;i<n;i++){
    if(inFrame(mem,pages[i])){ h++; cout<<"Page "<<pages[i]<<" HIT\n"; continue; }
    f++; mem[front]=pages[i]; front=(front+1)%frames;
    cout<<"Page "<<pages[i]<<" FAULT\n";
  }
  cout<<"FIFO: Faults="<<f<<" Hits="<<h<<"\n";
}
void lru(){
  int mem[frames],last[frames],f=0,h=0;
  fill(mem,mem+frames,-1); fill(last,last+frames,-1);
  for(int t=0;t<n;t++){
    if(inFrame(mem,pages[t])){
      h++; for(int j=0;j<frames;j++) if(mem[j]==pages[t]) last[j]=t;
      cout<<"Page "<<pages[t]<<" HIT\n"; continue;
    }
    f++; int rep=0,mn=INT_MAX;
    for(int j=0;j<frames;j++) if(last[j]<mn){ mn=last[j]; rep=j; }
    mem[rep]=pages[t]; last[rep]=t;
    cout<<"Page "<<pages[t]<<" FAULT\n";
  }
  cout<<"LRU: Faults="<<f<<" Hits="<<h<<"\n";
}
void optimal(){
  int mem[frames],f=0,h=0;
  fill(mem,mem+frames,-1);
  for(int i=0;i<n;i++){
    if(inFrame(mem,pages[i])){ h++; cout<<"Page "<<pages[i]<<" HIT\n"; continue; }
    f++; int rep=0,far=-1;
    for(int j=0;j<frames;j++){
      int nx=INT_MAX;
      for(int k=i+1;k<n;k++) if(pages[k]==mem[j]){ nx=k; break; }
      if(nx>far){ far=nx; rep=j; }
    }
    mem[rep]=pages[i]; cout<<"Page "<<pages[i]<<" FAULT\n";
  }
  cout<<"Optimal: Faults="<<f<<" Hits="<<h<<"\n";
}
int main(){
  cout<<"Frames: "; cin>>frames;
  cout<<"Page string length: "; cin>>n;
  cout<<"Enter pages:\n";
  for(int i=0;i<n;i++) cin>>pages[i];
  fifo(); lru(); optimal();
}
