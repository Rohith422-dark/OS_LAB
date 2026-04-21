#include<iostream>
#include<cmath>
#include<bitset>
using namespace std;

int bits(int x){
    int b = 0;
    while((1 << b) < x) b++;
    return b;
}
int main(){
    int ps, pg, nf;
    cout<<"Process size: ";
    cin>>ps;
    cout<<"Page/Frame size: ";
    cin>>pg;
    cout<<"Frames in memory: ";
    cin>>nf;
    int np = ceil((double)ps / pg);
    cout<<"\nPages required: "<<np<<"\n";
    if(np > nf){
        cout<<"Not enough frames!\n";
        return 0;
    }
    int pt[np];
    cout<<"Enter page table:\n";
    for(int i=0;i<np;i++){
        cout<<"Page "<<i<<": ";
        cin>>pt[i];
    }
    int offset_bits = bits(pg);
    int page_bits   = bits(np);
    int frame_bits  = bits(nf);
    cout<<"\nLogical -> Physical (Binary)\n\n";
    for(int la=0; la<ps; la++){
        int page = la / pg;
        int offset = la % pg;
        int frame = pt[page];
        int pa = frame * pg + offset;
        cout<<"Byte "<<la<<" ("<<bitset<8>(la)<<") -> ";
        cout<<"(Page "<<page<<" ("<<bitset<4>(page)<<"), ";
        cout<<"Offset "<<offset<<" ("<<bitset<4>(offset)<<")) -> ";
        cout<<"Frame "<<frame<<" ("<<bitset<4>(frame)<<") -> ";
        cout<<"Physical Address "<<pa<<" ("<<bitset<8>(pa)<<")\n";
    }
}
