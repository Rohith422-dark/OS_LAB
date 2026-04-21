#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

struct Frame{
  int pid;   // 0 = free, >0 = process id
};

int main(){
  int n,tf;
  cout<<"Processes TotalFrames: ";
  cin>>n>>tf;

  vector<int> req(n);
  int tot=0;

  cout<<"Enter requirement of each process:\n";
  for(int i=0;i<n;i++){
    cout<<"P"<<i+1<<": ";
    cin>>req[i];
    tot+=req[i];
  }

  // ✅ Frame array
  vector<Frame> frames(tf);
  for(int i=0;i<tf;i++) frames[i].pid=0;

  cout<<"\n--- Proportional Allocation ---\n";

  int idx=0;

  for(int i=0;i<n;i++){
    int f = (int)((double)req[i]/tot * tf);
    if(f<1) f=1;

    cout<<"P"<<i+1<<": "<<f<<" frames\n";

    for(int j=0;j<f && idx<tf;j++){
      frames[idx].pid=i+1;
      idx++;
    }
  }

  // remaining frames → free
  while(idx<tf){
    frames[idx].pid=0;
    idx++;
  }

  // ✅ Gantt Chart
  ofstream g("g.gp");

  g<<"set title 'Frame Allocation Gantt'\n";
  g<<"unset ytics\n";
  g<<"set yrange [0:2]\n";
  g<<"set xrange [0:"<<tf+1<<"]\n";

  int start=0;

  for(int i=0;i<tf;i++){
    int end=start+1;

    string color,label;

    if(frames[i].pid==0){
      color="white";
      label="Free";
    } else {
      color="skyblue";
      label="P"+to_string(frames[i].pid);
    }

    g<<"set obj rect from "<<start<<",0.6 to "
     <<end<<",1.4 fc rgb '"<<color<<"' fs solid border\n";

    g<<"set label '"<<label<<"' at "
     <<(start+end)/2<<",1 center\n";

    start=end;
  }

  g<<"plot 0 notitle\npause mouse close\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}