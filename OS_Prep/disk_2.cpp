#include<iostream>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<cstdlib>
using namespace std;

int req[20],n,head,dmin,dmax;

int move(int p[],int len){
  int s=0;
  for(int i=0;i<len-1;i++)
    s+=abs(p[i+1]-p[i]);
  return s;
}

// ✅ Plot function
void plot(string title,int path[],int k){
  ofstream g("g.gp");

  g<<"set title '"<<title<<"'\n";
  g<<"set xlabel 'Track'\n";
  g<<"set ylabel 'Order'\n";
  g<<"set xrange ["<<dmin<<":"<<dmax<<"]\n";
  g<<"set yrange [-1:"<<k<<"]\n";

  g<<"plot '-' using 1:2 with linespoints pt 7\n";

  for(int i=0;i<k;i++)
    g<<path[i]<<" "<<i<<"\n";

  g<<"e\npause mouse close\n";
  g.close();

  system("gnuplot g.gp");
}

// C-SCAN
void cscan(){
  int s[20];
  for(int i=0;i<n;i++) s[i]=req[i];
  sort(s,s+n);

  int path[50],k=0;
  path[k++]=head;

  for(int i=0;i<n;i++)
    if(s[i]>=head)
      path[k++]=s[i];

  path[k++]=dmax;
  path[k++]=dmin;

  for(int i=0;i<n;i++)
    if(s[i]<head)
      path[k++]=s[i];

  cout<<"\nC-SCAN: ";
  for(int i=0;i<k;i++) cout<<path[i]<<" ";

  cout<<"\nTotal: "<<move(path,k)<<"\n";

  plot("C-SCAN Disk Scheduling",path,k);
}

// LOOK
void look(){
  int s[20];
  for(int i=0;i<n;i++) s[i]=req[i];
  sort(s,s+n);

  int path[50],k=0;
  path[k++]=head;

  for(int i=0;i<n;i++)
    if(s[i]>=head)
      path[k++]=s[i];

  for(int i=n-1;i>=0;i--)
    if(s[i]<head)
      path[k++]=s[i];

  cout<<"\nLOOK: ";
  for(int i=0;i<k;i++) cout<<path[i]<<" ";

  cout<<"\nTotal: "<<move(path,k)<<"\n";

  plot("LOOK Disk Scheduling",path,k);
}

// C-LOOK
void clook(){
  int s[20];
  for(int i=0;i<n;i++) s[i]=req[i];
  sort(s,s+n);

  int path[50],k=0;
  path[k++]=head;

  for(int i=0;i<n;i++)
    if(s[i]>=head)
      path[k++]=s[i];

  for(int i=0;i<n;i++)
    if(s[i]<head)
      path[k++]=s[i];

  cout<<"\nC-LOOK: ";
  for(int i=0;i<k;i++) cout<<path[i]<<" ";

  cout<<"\nTotal: "<<move(path,k)<<"\n";

  plot("C-LOOK Disk Scheduling",path,k);
}

int main(){
  cout<<"dmin dmax n head: ";
  cin>>dmin>>dmax>>n>>head;

  cout<<"Requests:\n";
  for(int i=0;i<n;i++)
    cin>>req[i];

  cscan();
  look();
  clook();

  return 0;
}