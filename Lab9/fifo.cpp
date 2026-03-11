#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isInFrame(const vector<int>& frames, int page) {
    for (int p : frames) {
        if (p == page)
            return true;
    }
    return false;
}

int main() {
    vector<int> referenceString =
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    int numFrames = 3;

    vector<int> frames;
    queue<int> fifoQueue;

    int pageFaults = 0;

    cout << "FIFO Page Replacement Simulation\n\n";

    for (int page : referenceString) {
        cout << "Page: " << page << " -> ";

        if (!isInFrame(frames, page)) {
            pageFaults++;
            cout << "Page Fault | ";

            if (frames.size() < numFrames) {
                frames.push_back(page);
                fifoQueue.push(page);
            } else {
                int victim = fifoQueue.front();
                fifoQueue.pop();

                for (int i = 0; i < frames.size(); i++) {
                    if (frames[i] == victim) {
                        frames[i] = page;
                        break;
                    }
                }
                fifoQueue.push(page);
            }
        } else {
            cout << "Hit | ";
        }

        cout << "Frames: ";
        for (int f : frames)
            cout << f << " ";
        cout << endl;
    }

    double faultRate =
        (double)pageFaults / referenceString.size();

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Page Fault Rate: " << faultRate << endl;

    return 0;
}