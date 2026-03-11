#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fifo(const vector<int>& ref, int frames) {
    vector<int> mem;
    int idx = 0, faults = 0;

    for (int p : ref) {
        if (find(mem.begin(), mem.end(), p) == mem.end()) {
            faults++;
            if (mem.size() < frames)
                mem.push_back(p);
            else {
                mem[idx] = p;
                idx = (idx + 1) % frames;
            }
        }
    }
    return faults;
}

int lru(const vector<int>& ref, int frames) {
    vector<int> mem, last(frames, 0);
    int faults = 0, time = 0;

    for (int p : ref) {
        time++;
        auto it = find(mem.begin(), mem.end(), p);

        if (it == mem.end()) {
            faults++;
            if (mem.size() < frames) {
                mem.push_back(p);
                last[mem.size() - 1] = time;
            } else {
                int lruIdx = min_element(last.begin(), last.end()) - last.begin();
                mem[lruIdx] = p;
                last[lruIdx] = time;
            }
        } else {
            int idx = it - mem.begin();
            last[idx] = time;
        }
    }
    return faults;
}

int optimal(const vector<int>& ref, int frames) {
    vector<int> mem;
    int faults = 0;

    for (int i = 0; i < ref.size(); i++) {
        int p = ref[i];

        if (find(mem.begin(), mem.end(), p) == mem.end()) {
            faults++;
            if (mem.size() < frames) {
                mem.push_back(p);
            } else {
                int idx = -1, farthest = i + 1;

                for (int j = 0; j < mem.size(); j++) {
                    int k;
                    for (k = i + 1; k < ref.size(); k++)
                        if (ref[k] == mem[j])
                            break;

                    if (k == ref.size()) {
                        idx = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                mem[idx] = p;
            }
        }
    }
    return faults;
}

int main() {
    vector<int> reference =
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int frames = 3;

    int fifoFaults = fifo(reference, frames);
    int lruFaults = lru(reference, frames);
    int optFaults = optimal(reference, frames);

    cout << "Page Fault Comparison\n";
    cout << "---------------------\n";
    cout << "FIFO    : " << fifoFaults << endl;
    cout << "LRU     : " << lruFaults << endl;
    cout << "Optimal : " << optFaults << endl;

    return 0;
}