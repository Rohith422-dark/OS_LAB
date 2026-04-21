#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(){
    int nb,np;
    cout<<"Enter number of memory blocks: ";
    cin>>nb;

    vector<int> block(nb);
    cout<<"Enter block sizes:\n";
    for(int i=0;i<nb;i++) cin>>block[i];

    cout<<"\nEnter number of processes: ";
    cin>>np;

    vector<int> process(np);
    cout<<"Enter process sizes:\n";
    for(int i=0;i<np;i++) cin>>process[i];

    cout<<"\n1. First Fit\n2. Best Fit\n3. Worst Fit\n";
    int choice;
    cout<<"Enter choice: ";
    cin>>choice;

    vector<int> alloc(np,-1); // which block assigned

    // -------- Allocation Logic --------
    for(int i=0;i<np;i++){
        int idx=-1;

        if(choice==1){ // First Fit
            for(int j=0;j<nb;j++){
                if(block[j]>=process[i]){
                    idx=j;
                    break;
                }
            }
        }

        else if(choice==2){ // Best Fit
            int best=1e9;
            for(int j=0;j<nb;j++){
                if(block[j]>=process[i] && block[j]<best){
                    best=block[j];
                    idx=j;
                }
            }
        }

        else if(choice==3){ // Worst Fit
            int worst=-1;
            for(int j=0;j<nb;j++){
                if(block[j]>=process[i] && block[j]>worst){
                    worst=block[j];
                    idx=j;
                }
            }
        }

        if(idx!=-1){
            alloc[i]=idx;
            block[idx]-=process[i]; // reduce free space
        }
    }

    // -------- Output Table --------
    cout<<"\nProcess\tSize\tBlock\n";
    for(int i=0;i<np;i++){
        cout<<"P"<<i+1<<"\t"<<process[i]<<"\t";
        if(alloc[i]!=-1) cout<<alloc[i]+1<<"\n";
        else cout<<"Not Allocated\n";
    }
ofstream g("mem.gp");

g<<"set title 'Memory Allocation'\n";
g<<"set xrange [0:100]\n";
g<<"set yrange [0:"<<nb<<"]\n";

for(int i=0;i<np;i++){
    if(alloc[i]!=-1){
        g<<"set obj rect from 0,"<<alloc[i]
         <<" to "<<process[i]<<","<<alloc[i]+0.5
         <<" fc rgb 'blue'\n";
    }
}

g<<"plot 0\npause -1\n";
g.close();

system("gnuplot mem.gp");
}
