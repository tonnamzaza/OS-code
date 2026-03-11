#include <iostream>
#include <vector>
using namespace std;

class Frame {
public:
    int page;
    int lastUsed;

    Frame(int p, int t) {
        page = p;
        lastUsed = t;
    }
};

int findPage(const vector<Frame>& frames, int page) {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i].page == page)
            return i;
    }
    return -1;
}

int findLRU(const vector<Frame>& frames) {
    int lruIndex = 0;
    for (int i = 1; i < frames.size(); i++) {
        if (frames[i].lastUsed < frames[lruIndex].lastUsed)
            lruIndex = i;
    }
    return lruIndex;
}

int main() {
    vector<int> reference =
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int numFrames = 3;
    vector<Frame> frames;

    int time = 0;
    int pageFaults = 0;

    cout << "LRU Page Replacement Simulation\n\n";

    for (int page : reference) {
        time++;
        cout << "Page: " << page << " -> ";

        int index = findPage(frames, page);

        if (index != -1) {
            frames[index].lastUsed = time;
            cout << "Hit | ";
        } else {
            pageFaults++;
            cout << "Page Fault | ";

            if (frames.size() < numFrames) {
                frames.push_back(Frame(page, time));
            } else {
                int lru = findLRU(frames);
                frames[lru] = Frame(page, time);
            }
        }

        cout << "Frames: ";
        for (auto f : frames)
            cout << f.page << " ";
        cout << endl;
    }

    cout << "\nTotal Page Faults (LRU): " << pageFaults << endl;

    return 0;
}