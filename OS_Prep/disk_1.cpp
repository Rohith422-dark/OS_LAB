#include<iostream>
#include<algorithm>
#include<cmath>
#include<climits>
#include<fstream>
#include<cstdlib>
using namespace std;

int req[20], n, head, dmin, dmax;

// movement calculation
int move(int p[], int len){
    int s = 0;
    for(int i = 0; i < len - 1; i++)
        s += abs(p[i+1] - p[i]);
    return s;
}

// Gnuplot function
void plot(string title, int path[], int k){
    ofstream g("g.gp");

    g << "set title '" << title << "'\n";
    g << "set xlabel 'Track'\n";
    g << "set ylabel 'Order'\n";
    g << "set xrange [" << dmin << ":" << dmax << "]\n";
    g << "set yrange [-1:" << k << "]\n";

    g << "plot '-' using 1:2 with linespoints pt 7\n";

    for(int i = 0; i < k; i++)
        g << path[i] << " " << i << "\n";

    g << "e\npause mouse close\n";
    g.close();

    system("gnuplot g.gp");
}

// FCFS
void fcfs(){
    int path[50], k = 0;

    path[k++] = head;
    for(int i = 0; i < n; i++)
        path[k++] = req[i];

    cout << "\nFCFS: ";
    for(int i = 0; i < k; i++) cout << path[i] << " ";

    cout << "\nTotal Movement: " << move(path, k) << "\n";

    plot("FCFS Disk Scheduling", path, k);
}

// SSTF
void sstf(){
    bool done[20] = {};
    int cur = head;
    int path[50], k = 0;

    path[k++] = cur;

    for(int i = 0; i < n; i++){
        int sel = -1, mn = INT_MAX;

        for(int j = 0; j < n; j++){
            if(!done[j] && abs(req[j] - cur) < mn){
                mn = abs(req[j] - cur);
                sel = j;
            }
        }

        cur = req[sel];
        done[sel] = true;
        path[k++] = cur;
    }

    cout << "\nSSTF: ";
    for(int i = 0; i < k; i++) cout << path[i] << " ";

    cout << "\nTotal Movement: " << move(path, k) << "\n";

    plot("SSTF Disk Scheduling", path, k);
}

// SCAN (both directions)
void scan(){
    int s[20];
    for(int i = 0; i < n; i++) s[i] = req[i];

    sort(s, s + n);

    int path[50], k = 0;
    path[k++] = head;

    int dir;
    cout << "\nEnter direction (1 = RIGHT, 2 = LEFT): ";
    cin >> dir;

    if(dir == 1){  // RIGHT
        for(int i = 0; i < n; i++)
            if(s[i] >= head)
                path[k++] = s[i];

        path[k++] = dmax;

        for(int i = n - 1; i >= 0; i--)
            if(s[i] < head)
                path[k++] = s[i];

        cout << "\nSCAN RIGHT: ";
    }

    else if(dir == 2){  // LEFT
        for(int i = n - 1; i >= 0; i--)
            if(s[i] <= head)
                path[k++] = s[i];

        path[k++] = dmin;

        for(int i = 0; i < n; i++)
            if(s[i] > head)
                path[k++] = s[i];

        cout << "\nSCAN LEFT: ";
    }

    else{
        cout << "Invalid direction\n";
        return;
    }

    for(int i = 0; i < k; i++) cout << path[i] << " ";

    cout << "\nTotal Movement: " << move(path, k) << "\n";

    plot("SCAN Disk Scheduling", path, k);
}

// MAIN
int main(){
    cout << "Enter dmin dmax n head: ";
    cin >> dmin >> dmax >> n >> head;

    cout << "Enter Requests:\n";
    for(int i = 0; i < n; i++)
        cin >> req[i];

    cout << "\n1. FCFS\n2. SSTF\n3. SCAN\nEnter choice: ";
    int ch;
    cin >> ch;

    switch(ch){
        case 1: fcfs(); break;
        case 2: sstf(); break;
        case 3: scan(); break;
        default: cout << "Invalid choice\n";
    }

    return 0;
}
