#include<iostream>
#include<climits>
using namespace std;
int n,m;
int alloc[10][10],maxm[10][10],need[10][10],avail[10],work[10];
bool finish[10];
int main(){
  cout<<"Processes Resources: "; cin>>n>>m;
  cout<<"Total resources: "; for(int j=0;j<m;j++) cin>>avail[j];
  cout<<"Max matrix:\n";
  for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>maxm[i][j];
  cout<<"Alloc matrix:\n";
  for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>alloc[i][j];
  for(int j=0;j<m;j++){
  work[j] = avail[j];
}
  for(int i=0;i<n;i++) for(int j=0;j<m;j++)
    need[i][j]=maxm[i][j]-alloc[i][j];
  int seq[n],k=0;
  for(int pass=0;pass<n;pass++){
    for(int i=0;i<n;i++){
      if(finish[i]) continue;
      bool ok=true;
      for(int j=0;j<m;j++) if(need[i][j]>work[j]){ ok=false; break; }
      if(ok){
        for(int j=0;j<m;j++) work[j]+=alloc[i][j];
        finish[i]=true; seq[k++]=i;
      }
    }
  }
  bool safe=true; for(int i=0;i<n;i++) if(!finish[i]){ safe=false; break; }
  if(safe){
    cout<<"SAFE STATE\nSequence: ";
    for(int i=0;i<k;i++) cout<<"P"<<seq[i]<<(i<k-1?"->":"");
    cout<<"\n";
  } else cout<<"DEADLOCK STATE\n";
}
