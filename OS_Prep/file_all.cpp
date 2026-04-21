#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout << "Enter Number of Locations: ";
    cin >> n;
    vector<bool> disk(n);
    cout << "Enter disk (0/1): ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        disk[i] = (x == 1);
    }
    cout << "1. seq\n2. link\n3. inde\n";
    int c;
    cout << "enter option: ";
    cin >> c;
    int num;
    cout << "enter number of files: ";
    cin >> num;
    vector<int> files(num);
    cout << "Enter file sizes: ";
    for (int i = 0; i < num; i++) cin >> files[i];
    for (int f = 0; f < num; f++) {
        int s = files[f];
        cout << "f size: " << s << endl;
        if (c == 1) {  // Sequential
            bool acc = false;
            for (int i = 0; i <= n - s; i++) {
                bool free = true;
                for (int j = i; j < i + s; j++) {
                    if (disk[j]) {
                        free = false;
                        break;
                    }
                }
                if (free) {
                    for (int j = i; j < i + s; j++)
                        disk[j] = true;
                    cout << "Allocated blocks: ";
                    for (int j = i; j < i + s; j++)
                        cout << j << " ";
                    cout << endl;
                    cout << "Stored at positions: "
                         << i << " to " << i + s - 1 << endl;
                    acc = true;
                    break;
                }
            }
            if (!acc) cout << "no space left\n";
        }
        else if (c == 2) {  // Linked
            vector<int> free;
            for (int i = 0; i < n; i++)
                if (!disk[i]) free.push_back(i);
            if (free.size() < s) {
                cout << "no space left\n";
            } else {
                vector<int> accblock(free.begin(), free.begin() + s);
                for (int x : accblock) disk[x] = true;
                cout << "Allocated blocks (linked):\n";
                for (int i = 0; i < accblock.size(); i++) {
                    cout << accblock[i];
                    if (i != accblock.size() - 1) cout << " -> ";
                }
                cout << endl;
                cout << "Stored at positions: ";
                for (int x : accblock) cout << x << " ";
                cout << endl;
            }
        }
        else if (c == 3) {  // Indexed
            vector<int> free;
            for (int i = 0; i < n; i++)
                if (!disk[i]) free.push_back(i);
            if (free.size() < s + 1) {
                cout << "no space left\n";
            } else {
                int index = free[0];
                disk[index] = true;
                vector<int> accblock(free.begin() + 1, free.begin() + 1 + s);
                for (int x : accblock) disk[x] = true;
                cout << "indexblock: " << index << endl;
                cout << "datablocks: [";
                for (int i = 0; i < accblock.size(); i++) {
                    cout << accblock[i];
                    if (i != accblock.size() - 1) cout << ", ";
                }
                cout << "]\n";
            }
        }
        else {
            cout << "invalid\n";
            break;
        }
        // Print disk state
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << "'" << (disk[i] ? "1" : "0") << "'";
            if (i != n - 1) cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}
