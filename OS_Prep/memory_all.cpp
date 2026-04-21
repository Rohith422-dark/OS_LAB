#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;

struct Hole{
  int size;
  string status;   // "OS" / "free" / "used"
  string file;
  int fsize;
};

int main(){
  int n,f;
  cout<<"Holes: "; cin>>n;

  vector<Hole> h(n);

  for(int i=0;i<n;i++){
    cout<<"Size Status(OS/free): ";
    cin>>h[i].size>>h[i].status;
    h[i].file="";
    h[i].fsize=0;
  }

  cout<<"Files: "; cin>>f;

  vector<int> fs(f);
  vector<string> fn(f);

  for(int i=0;i<f;i++){
    cout<<"Name Size: ";
    cin>>fn[i]>>fs[i];
  }

  int ch;
  cout<<"1=FF 2=BF 3=WF: ";
  cin>>ch;

  vector<Hole> holes=h;

  // ✅ Allocation logic
  for(int i=0;i<f;i++){
    int sel=-1;
    int best=(ch==2?INT_MAX:-1);

    for(int j=0;j<n;j++){
      if(holes[j].status=="free" && holes[j].size>=fs[i]){
        int d=holes[j].size-fs[i];

        if(ch==1){ sel=j; break; }
        if(ch==2 && d<best){ best=d; sel=j; }
        if(ch==3 && d>best){ best=d; sel=j; }
      }
    }

    if(sel!=-1){
      holes[sel].file=fn[i];
      holes[sel].fsize=fs[i];
      holes[sel].status="used";
    }
    else{
      cout<<fn[i]<<": Failed\n";
    }
  }

  cout<<"\nHole\tSize\tFile/Status\n";
  for(int i=0;i<n;i++){
    cout<<i+1<<"\t"<<holes[i].size<<"\t"
        <<(holes[i].file.empty()?holes[i].status:holes[i].file)<<"\n";
  }

  // ✅ Gantt Chart Code
  ofstream g("g.gp");

  int start=0,total=0;
  for(auto &x:holes) total+=x.size;

  g<<"set title 'Memory Allocation Gantt'\n";
  g<<"unset ytics\n";
  g<<"set yrange [0:2]\n";
  g<<"set xrange [0:"<<total+10<<"]\n";

  for(auto &x:holes){
    int end=start+x.size;

    string color,label;

    if(x.status=="OS"){
      color="red";
      label="OS";
    }
    else if(x.status=="free"){
      color="white";
      label="Free";
    }
    else{
      color="skyblue";
      label=x.file;
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