#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

/* ---------------- CONFIG ---------------- */
const int PAGE_SIZE = 1024;
const int NUM_FRAMES = 4;
const int TLB_SIZE = 2;
const int DELTA = 3;

const int TLB_TIME = 20;
const int MEM_TIME = 100;

/* ---------------- STRUCTS ---------------- */
struct PageTableEntry {
    int frame;
    bool valid;
};

struct TLBEntry {
    int page;
    int frame;
    int lastUsed;
};

/* ---------------- GLOBALS ---------------- */
vector<int> frames(NUM_FRAMES, -1);
map<int, PageTableEntry> pageTable;
vector<TLBEntry> tlb;
vector<int> reference;
int timeCounter = 0;
int pageFaults = 0;
int tlbHits = 0;

/* ---------------- FUNCTIONS ---------------- */

int findTLB(int page) {
    for (int i = 0; i < tlb.size(); i++)
        if (tlb[i].page == page)
            return i;
    return -1;
}

int findFreeFrame() {
    for (int i = 0; i < NUM_FRAMES; i++)
        if (frames[i] == -1)
            return i;
    return -1;
}

int replaceFrameFIFO() {
    static int ptr = 0;
    int victim = ptr;
    ptr = (ptr + 1) % NUM_FRAMES;
    return victim;
}

void updateTLB(int page, int frame) {
    if (tlb.size() < TLB_SIZE)
        tlb.push_back({page, frame, timeCounter});
    else {
        int lru = 0;
        for (int i = 1; i < tlb.size(); i++)
            if (tlb[i].lastUsed < tlb[lru].lastUsed)
                lru = i;
        tlb[lru] = {page, frame, timeCounter};
    }
}

void workingSet(int t) {
    set<int> ws;
    int start = max(0, t - DELTA + 1);
    for (int i = start; i <= t; i++)
        ws.insert(reference[i]);

    cout << "Working Set: {";
    bool first = true;
    for (int p : ws) {
        if (!first) cout << ",";
        cout << p;
        first = false;
    }
    cout << "} Size=" << ws.size();

    if (ws.size() > NUM_FRAMES)
        cout << "  **THRASHING**";
    cout << endl;
}

/* ---------------- MAIN ---------------- */
int main() {
    reference = {7,0,1,2,0,3,0,4,2,3,0};

    double totalAccessTime = 0;

    for (int i = 0; i < reference.size(); i++) {
        int page = reference[i];
        timeCounter++;

        cout << "\nAccess Page: " << page << endl;

        int tlbIndex = findTLB(page);

        if (tlbIndex != -1) {
            tlbHits++;
            tlb[tlbIndex].lastUsed = timeCounter;
            totalAccessTime += TLB_TIME;
            cout << "TLB HIT → Frame " << tlb[tlbIndex].frame << endl;
        } else {
            totalAccessTime += TLB_TIME + MEM_TIME;

            if (!pageTable[page].valid) {
                pageFaults++;
                cout << "PAGE FAULT!" << endl;

                int frame = findFreeFrame();
                if (frame == -1)
                    frame = replaceFrameFIFO();

                frames[frame] = page;
                pageTable[page] = {frame, true};
                updateTLB(page, frame);
            } else {
                updateTLB(page, pageTable[page].frame);
            }
        }

        cout << "Frames: ";
        for (int f : frames)
            cout << f << " ";
        cout << endl;

        workingSet(i);
    }

    cout << "\n=========== STATISTICS ===========\n";
    cout << "Page Faults: " << pageFaults << endl;
    cout << "TLB Hits: " << tlbHits << endl;
    cout << "TLB Hit Ratio: "
         << (double)tlbHits / reference.size() << endl;
    cout << "Average Access Time: "
         << totalAccessTime / reference.size()
         << " ns\n";

    return 0;
}