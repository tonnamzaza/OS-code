#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <iomanip>

using namespace std;

class PageReplacementFIFO {
private:
    int numFrames;
    queue<int> frameQueue;
    unordered_set<int> frameSet;
    int pageFaults;
    vector<vector<int>> frameHistory;

public:
    PageReplacementFIFO(int frames)
        : numFrames(frames), pageFaults(0) {}

    void referencePage(int page) {
        cout << "\nReferencing page: " << page << endl;

        // HIT
        if (frameSet.find(page) != frameSet.end()) {
            cout << "Page " << page << " already in memory (HIT)\n";
        }
        // PAGE FAULT
        else {
            pageFaults++;
            cout << "PAGE FAULT #" << pageFaults << endl;

            if (frameQueue.size() >= numFrames) {
                int removedPage = frameQueue.front();
                frameQueue.pop();
                frameSet.erase(removedPage);
                cout << "Removed page " << removedPage
                     << " (oldest)\n";
            }

            frameQueue.push(page);
            frameSet.insert(page);
            cout << "Loaded page " << page << " into memory\n";
        }

        // Save frame history
        vector<int> currentFrames;
        queue<int> temp = frameQueue;
        while (!temp.empty()) {
            currentFrames.push_back(temp.front());
            temp.pop();
        }
        frameHistory.push_back(currentFrames);

        // Display frames
        cout << "Frames: [";
        for (size_t i = 0; i < currentFrames.size(); i++) {
            cout << currentFrames[i];
            if (i < currentFrames.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }

    void simulate(const vector<int>& referenceString) {
        cout << "\n===== FIFO PAGE REPLACEMENT SIMULATION =====\n";
        cout << "Number of Frames: " << numFrames << endl;
        cout << "Reference String: ";
        for (int p : referenceString)
            cout << p << " ";
        cout << "\n\n";

        for (int p : referenceString)
            referencePage(p);

        displayResults();
        displayTable(referenceString);
    }

    void displayResults() {
        cout << "\n===== RESULTS =====\n";
        cout << "Total Page Faults: " << pageFaults << endl;

        int totalRefs = frameHistory.size();
        double faultRate = (double)pageFaults / totalRefs * 100.0;
        double hitRate = 100.0 - faultRate;

        cout << "Total References: " << totalRefs << endl;
        cout << fixed << setprecision(2);
        cout << "Page Fault Rate: " << faultRate << " %\n";
        cout << "Hit Rate: " << hitRate << " %\n";
    }

    void displayTable(const vector<int>& referenceString) {
        cout << "\n===== FRAME CONTENTS TABLE =====\n";

        cout << setw(8) << "Step |";
        for (int p : referenceString)
            cout << setw(4) << p;
        cout << endl;

        cout << string(8 + 1 + referenceString.size() * 4, '-') << endl;

        for (int frame = 0; frame < numFrames; frame++) {
            cout << setw(8) << ("Frame " + to_string(frame)) << "|";
            for (size_t step = 0; step < frameHistory.size(); step++) {
                if (frame < frameHistory[step].size())
                    cout << setw(4) << frameHistory[step][frame];
                else
                    cout << setw(4) << "-";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "PAGE REPLACEMENT ALGORITHM - FIFO\n";
    cout << "=================================\n";

    // Test Case 1
    cout << "\n--- TEST CASE 1 ---\n";
    PageReplacementFIFO fifo1(3);
    vector<int> refString1 = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    fifo1.simulate(refString1);

    // Test Case 2
    cout << "\n--- TEST CASE 2 ---\n";
    PageReplacementFIFO fifo2(4);
    vector<int> refString2 = {1,2,3,4,1,2,5,1,2,3,4,5};
    fifo2.simulate(refString2);

    // Interactive mode
    char choice;
    cout << "\nRun custom test? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int frames;
        cout << "Enter number of frames: ";
        cin >> frames;

        PageReplacementFIFO customFIFO(frames);
        cout << "Enter reference string (-1 to stop):\n";

        vector<int> customRef;
        int page;
        while (cin >> page && page != -1)
            customRef.push_back(page);

        customFIFO.simulate(customRef);
    }

    return 0;
}
