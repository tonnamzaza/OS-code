#include <iostream>
#include <list>
#include <unordered_map>
#include <iomanip>

using namespace std;

const int TLB_SIZE = 8;

class TLB {
private:
    struct TLBEntry {
        int pageNumber;
        int frameNumber;
        TLBEntry(int p, int f) : pageNumber(p), frameNumber(f) {}
    };

    list<TLBEntry> tlbCache;   // MRU at front
    unordered_map<int, list<TLBEntry>::iterator> tlbMap;
    int hits;
    int misses;

public:
    TLB() : hits(0), misses(0) {}

    int lookup(int pageNumber) {
        auto it = tlbMap.find(pageNumber);

        if (it != tlbMap.end()) {
            // TLB Hit
            hits++;
            int frameNumber = it->second->frameNumber;

            // Move to front (LRU)
            tlbCache.splice(tlbCache.begin(), tlbCache, it->second);

            cout << "TLB HIT  : Page " << pageNumber
                 << " -> Frame " << frameNumber << endl;

            return frameNumber;
        } else {
            // TLB Miss
            misses++;
            cout << "TLB MISS : Page " << pageNumber
                 << " not in TLB" << endl;
            return -1;
        }
    }

    void insert(int pageNumber, int frameNumber) {
        // If already exists, update & move to front
        if (tlbMap.find(pageNumber) != tlbMap.end()) {
            auto it = tlbMap[pageNumber];
            it->frameNumber = frameNumber;
            tlbCache.splice(tlbCache.begin(), tlbCache, it);
            return;
        }

        // Remove LRU if full
        if (tlbCache.size() >= TLB_SIZE) {
            int removedPage = tlbCache.back().pageNumber;
            cout << "TLB FULL : Removing page "
                 << removedPage << " (LRU)" << endl;
            tlbMap.erase(removedPage);
            tlbCache.pop_back();
        }

        // Insert new entry
        tlbCache.push_front(TLBEntry(pageNumber, frameNumber));
        tlbMap[pageNumber] = tlbCache.begin();

        cout << "TLB INSERT : Page " << pageNumber
             << " -> Frame " << frameNumber << endl;
    }

    void displayTLB() {
        cout << "\n=== TLB CONTENTS (MRU -> LRU) ===\n";
        cout << setw(10) << "Page#"
             << setw(10) << "Frame#\n";
        cout << string(20, '-') << endl;

        for (const auto& entry : tlbCache) {
            cout << setw(10) << entry.pageNumber
                 << setw(10) << entry.frameNumber << endl;
        }
    }

    void displayStats() {
        int total = hits + misses;
        double hitRatio = (total > 0) ?
            (double)hits / total * 100 : 0;

        cout << "\n=== TLB STATISTICS ===\n";
        cout << "Total Accesses : " << total << endl;
        cout << "Hits           : " << hits << endl;
        cout << "Misses         : " << misses << endl;
        cout << "Hit Ratio      : "
             << fixed << setprecision(2)
             << hitRatio << " %" << endl;
    }
};

// Memory System with Page Table
class MemorySystem {
private:
    TLB tlb;
    unordered_map<int, int> pageTable;

public:
    MemorySystem() {
        // Page Table Initialization
        pageTable[0] = 5;
        pageTable[1] = 2;
        pageTable[2] = 8;
        pageTable[3] = 1;
        pageTable[4] = 9;
        pageTable[5] = 3;
        pageTable[6] = 7;
        pageTable[7] = 4;
    }

    int translateAddress(int pageNumber) {
        cout << "\n--- Translating Page "
             << pageNumber << " ---\n";

        // TLB lookup
        int frame = tlb.lookup(pageNumber);

        if (frame == -1) {
            // Page Table lookup
            if (pageTable.find(pageNumber) != pageTable.end()) {
                frame = pageTable[pageNumber];

                cout << "Page Table : Page "
                     << pageNumber << " -> Frame "
                     << frame << endl;

                // Insert into TLB
                tlb.insert(pageNumber, frame);
            } else {
                cout << "PAGE FAULT : Page "
                     << pageNumber << " not in memory!\n";
                return -1;
            }
        }

        return frame;
    }

    void displayStatus() {
        tlb.displayTLB();
        tlb.displayStats();
    }
};

int main() {
    cout << "TLB SIMULATION\n";
    cout << "==============\n";
    cout << "TLB Size            : "
         << TLB_SIZE << " entries\n";
    cout << "Replacement Policy  : LRU\n\n";

    MemorySystem memSys;

    int referenceString[] =
        {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 5, 6, 7, 0, 1};

    int numReferences =
        sizeof(referenceString) / sizeof(referenceString[0]);

    cout << "Reference String : ";
    for (int i = 0; i < numReferences; i++) {
        cout << referenceString[i] << " ";
    }
    cout << "\n\n";

    // Process references
    for (int i = 0; i < numReferences; i++) {
        memSys.translateAddress(referenceString[i]);
    }

    // Final report
    memSys.displayStatus();

    return 0;
}
