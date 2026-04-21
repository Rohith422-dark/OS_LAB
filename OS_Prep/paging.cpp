#include<iostream>
#include<cmath>
using namespace std;
int main(){
  int ps,pg,nf;
  cout<<"Process size: "; cin>>ps;
  cout<<"Page/Frame size: "; cin>>pg;
  cout<<"Frames in memory: "; cin>>nf;
  int np=(int)ceil((double)ps/pg);
  cout<<"\nPages required: "<<np<<"\n";
  if(np>nf){ cout<<"Not enough frames!\n"; return 0; }
  int pt[np];
  cout<<"Enter page table (frame for each page):\n";
  for(int i=0;i<np;i++){ cout<<"Page "<<i<<": "; cin>>pt[i]; }
  cout<<"\nLogical -> Physical\n";
  for(int la=0;la<ps;la++){
    int page=la/pg, offset=la%pg;
    int pa=pt[page]*pg+offset;
    cout<<"LA="<<la<<" (P"<<page<<",Off="<<offset<<") -> PA="<<pa<<"\n";
  }
}
