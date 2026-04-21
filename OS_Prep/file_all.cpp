

#include<iostream>
#include<vector>
using namespace std;

int main(){
  int diskSize; 
  cout<<"Disk size: "; 
  cin>>diskSize;

  vector<bool> used(diskSize,false);

  int occ; 
  cout<<"Pre-occupied blocks: "; 
  cin>>occ;

  for(int i=0;i<occ;i++){ 
    int b; 
    cin>>b; 
    used[b]=true; 
  }

  int nf; 
  cout<<"Files: "; 
  cin>>nf;

  // ✅ fixed (no VLA)
  vector<string> fname(nf);  
  vector<int> need(nf);

  for(int i=0;i<nf;i++){
    cout<<"Name blocks for file "<<i+1<<": ";
    cin>>fname[i]>>need[i];
  }

  auto getFree=[&](vector<int>&v,int cnt,vector<bool>&u){
    for(int i=0;i<diskSize&&(int)v.size()<cnt;i++)
      if(!u[i]){ v.push_back(i); u[i]=true; }
  };

  // Sequential
  cout<<"\n--- Sequential ---\n";
  vector<bool> uS=used;

  for(int i=0;i<nf;i++){
    bool ok=false;

    for(int s=0;s<=diskSize-need[i];s++){
      bool fr=true;

      for(int k=s;k<s+need[i];k++)
        if(uS[k]){ fr=false; break; }

      if(fr){
        cout<<fname[i]<<": ";
        for(int k=s;k<s+need[i];k++){
          cout<<k<<" ";
          uS[k]=true;
        }
        cout<<"\n";
        ok=true;
        break;
      }
    }

    if(!ok) cout<<fname[i]<<": Failed\n";
  }

  // Indexed
  cout<<"\n--- Indexed ---\n";
  vector<bool> uI=used;

  for(int i=0;i<nf;i++){
    vector<int> b;
    getFree(b,need[i]+1,uI);

    if((int)b.size()<need[i]+1){
      cout<<fname[i]<<": Failed\n";
      continue;
    }

    cout<<fname[i]<<" inode="<<b[0]<<" data: ";
    for(int k=1;k<=need[i];k++) cout<<b[k]<<" ";
    cout<<"\n";
  }

  // Linked
  cout<<"\n--- Linked ---\n";
  vector<bool> uL=used;

  for(int i=0;i<nf;i++){
    vector<int> b;
    getFree(b,need[i],uL);

    if(b.empty()){
      cout<<fname[i]<<": Failed\n";
      continue;
    }

    cout<<fname[i]<<": ";
    for(int k=0;k<(int)b.size()-1;k++)
      cout<<b[k]<<"->";

    cout<<b.back()<<"->NULL\n";
  }

  /*
  Gantt chart not applicable for file allocation.
  Output itself is block diagram:
  Sequential → blocks in order
  Indexed → inode -> blocks
  Linked → chain of blocks
  */

  return 0;
}
