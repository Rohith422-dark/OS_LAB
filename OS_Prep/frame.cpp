#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

struct Frame{
  int pid;
};

int main(){
  int tf,n;

  cout<<"Enter total frames: ";
  cin>>tf;

  vector<int> frameSize(tf);
  cout<<"Frame size:\n";
  for(int i=0;i<tf;i++){
    cout<<i+1<<" ";
    cin>>frameSize[i];   // (just for input display like notebook)
  }

  cout<<"\nEnter number of processes: ";
  cin>>n;

  vector<int> req(n);
  int totalReq=0;

  cout<<"Process  Requirement\n";
  for(int i=0;i<n;i++){
    cout<<"P"<<i+1<<" ";
    cin>>req[i];
    totalReq += req[i];
  }

  cout<<"\n1. Minimum\n2. Equal\n3. Proportional\nChoice: ";
  int ch;
  cin>>ch;

  vector<int> alloc(n,0);

  // ✅ Allocation logic
  if(ch==1){  // Minimum
    for(int i=0;i<n;i++)
      alloc[i]=1;
  }
  else if(ch==2){ // Equal
    int each = tf/n;
    for(int i=0;i<n;i++)
      alloc[i]=each;
  }
  else if(ch==3){ // Proportional
    for(int i=0;i<n;i++){
      alloc[i] = (double)req[i]/totalReq * tf;
      if(alloc[i]<1) alloc[i]=1;
    }
  }
  else{
    cout<<"Invalid choice\n";
    return 0;
  }

  cout<<"\n--- Allocation ---\n";
  for(int i=0;i<n;i++)
    cout<<"P"<<i+1<<" : "<<alloc[i]<<"\n";

  // ✅ Frame assignment
  vector<Frame> frames(tf);
  int idx=0;

  for(int i=0;i<n;i++){
    for(int j=0;j<alloc[i] && idx<tf;j++){
      frames[idx].pid=i+1;
      idx++;
    }
  }

  while(idx<tf){
    frames[idx].pid=0;
    idx++;
  }

  // ✅ Gnuplot (VERTICAL MEMORY BLOCK like your image)
  ofstream g("g.gp");

  g<<"set title 'Memory Allocation'\n";
  g<<"unset xtics\n";
  g<<"unset ytics\n";
  g<<"set xrange [0:2]\n";
  g<<"set yrange [0:"<<tf<<"]\n";

  int start=0;

  for(int i=0;i<tf;i++){
    int end = start + 1;

    string color,label;

    if(frames[i].pid==0){
      color="white";
      label="Free";
    }
    else{
      color="skyblue";
      label="P"+to_string(frames[i].pid);
    }

    // vertical blocks
    g<<"set obj rect from 0.5,"<<start
     <<" to 1.5,"<<end
     <<" fc rgb '"<<color<<"' fs solid border\n";

    g<<"set label '"<<label<<"' at 1,"
     <<(start+end)/2<<" center\n";

    start=end;
  }

  g<<"plot 0 notitle\npause mouse close\n";
  g.close();

  system("gnuplot g.gp");

  return 0;
}
