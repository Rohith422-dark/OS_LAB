#include<iostream>
#include<climits>
#include<iomanip>
using namespace std;

int frames,n,pages[100];

bool inFrame(int mem[],int p){
  for(int i=0;i<frames;i++)
    if(mem[i]==p) return true;
  return false;
}

// Print table row
void printRow(int mem[], int page, char status){
  cout<<setw(5)<<page<<" | ";
  for(int i=0;i<frames;i++){
    if(mem[i]==-1) cout<<"- ";
    else cout<<mem[i]<<" ";
  }
  cout<<"| "<<status<<"\n";
}

// FIFO
void fifo(){
  cout<<"\n--- FIFO ---\n";
  cout<<"Page | Frames | Status\n";

  int mem[frames],front=0,f=0,h=0;
  fill(mem,mem+frames,-1);

  for(int i=0;i<n;i++){
    if(inFrame(mem,pages[i])){
      h++;
      printRow(mem,pages[i],'H');
    }
    else{
      f++;
      mem[front]=pages[i];
      front=(front+1)%frames;
      printRow(mem,pages[i],'F');
    }
  }
  cout<<"Faults="<<f<<" Hits="<<h<<"\n";
}

// LRU
void lru(){
  cout<<"\n--- LRU ---\n";
  cout<<"Page | Frames | Status\n";

  int mem[frames],last[frames],f=0,h=0;
  fill(mem,mem+frames,-1);
  fill(last,last+frames,-1);

  for(int t=0;t<n;t++){
    if(inFrame(mem,pages[t])){
      h++;
      for(int j=0;j<frames;j++)
        if(mem[j]==pages[t]) last[j]=t;

      printRow(mem,pages[t],'H');
    }
    else{
      f++;
      int rep=0,mn=INT_MAX;

      for(int j=0;j<frames;j++){
        if(last[j]<mn){
          mn=last[j];
          rep=j;
        }
      }

      mem[rep]=pages[t];
      last[rep]=t;

      printRow(mem,pages[t],'F');
    }
  }
  cout<<"Faults="<<f<<" Hits="<<h<<"\n";
}

// OPTIMAL
void optimal(){
  cout<<"\n--- OPTIMAL ---\n";
  cout<<"Page | Frames | Status\n";

  int mem[frames],f=0,h=0;
  fill(mem,mem+frames,-1);

  for(int i=0;i<n;i++){
    if(inFrame(mem,pages[i])){
      h++;
      printRow(mem,pages[i],'H');
    }
    else{
      f++;
      int rep=0,far=-1;

      for(int j=0;j<frames;j++){
        int nx=INT_MAX;
        for(int k=i+1;k<n;k++){
          if(pages[k]==mem[j]){
            nx=k;
            break;
          }
        }
        if(nx>far){
          far=nx;
          rep=j;
        }
      }

      mem[rep]=pages[i];
      printRow(mem,pages[i],'F');
    }
  }
  cout<<"Faults="<<f<<" Hits="<<h<<"\n";
}

// MAIN
int main(){
  cout<<"Frames: ";
  cin>>frames;

  cout<<"Page string length: ";
  cin>>n;

  cout<<"Enter pages:\n";
  for(int i=0;i<n;i++)
    cin>>pages[i];

  cout<<"\n1. FIFO\n2. LRU\n3. OPTIMAL\nEnter choice: ";
  int ch;
  cin>>ch;

  switch(ch){
    case 1: fifo(); break;
    case 2: lru(); break;
    case 3: optimal(); break;
    default: cout<<"Invalid choice\n";
  }

  return 0;
}
