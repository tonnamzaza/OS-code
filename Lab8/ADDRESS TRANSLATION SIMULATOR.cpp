#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_PAGES  = 64;
const int NUM_FRAMES = 32;
const int PAGE_SIZE  = 1024;

class PageTable {
private:
    int  pageTable[NUM_PAGES];
    bool valid[NUM_PAGES];

public:
    PageTable() {
        srand(time(0));
        bool usedFrames[NUM_FRAMES] = {false};

        for (int i = 0; i < NUM_PAGES; i++) {
            // 75% chance that page is valid
            if (rand() % 100 < 75) {
                int frame;
                do {
                    frame = rand() % NUM_FRAMES;
                } while (usedFrames[frame]);

                pageTable[i] = frame;
                valid[i] = true;
                usedFrames[frame] = true;
            } else {
                pageTable[i] = -1;
                valid[i] = false;
            }
        }
    }

    int translateAddress(int logicalAddress) {
        int pageNumber = logicalAddress / PAGE_SIZE;
        int offset     = logicalAddress % PAGE_SIZE;

        if (pageNumber < 0 || pageNumber >= NUM_PAGES) {
            cout << "Error: Invalid page number " << pageNumber << endl;
            return -1;
        }

        if (!valid[pageNumber]) {
            cout << "Page Fault: Page " << pageNumber
                 << " is not in memory" << endl;
            return -1;
        }

        int frameNumber     = pageTable[pageNumber];
        int physicalAddress = frameNumber * PAGE_SIZE + offset;

        cout << "Logical Address  : " << logicalAddress << endl;
        cout << "Page Number      : " << pageNumber << endl;
        cout << "Offset           : " << offset << endl;
        cout << "Frame Number     : " << frameNumber << endl;
        cout << "Physical Address : " << physicalAddress << endl;

        return physicalAddress;
    }

    void displayPageTable() {
        cout << "\n===== PAGE TABLE =====\n";
        cout << setw(10) << "Page#"
             << setw(10) << "Frame#"
             << setw(10) << "Valid" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < NUM_PAGES; i++) {
            cout << setw(10) << i;

            if (valid[i])
                cout << setw(10) << pageTable[i]
                     << setw(10) << "Yes";
            else
                cout << setw(10) << "N/A"
                     << setw(10) << "No";

            cout << endl;
        }
    }
};

int main() {
    cout << "ADDRESS TRANSLATION SIMULATOR\n";
    cout << "============================\n";
    cout << "Page Size       : " << PAGE_SIZE << " bytes\n";
    cout << "Number of Pages : " << NUM_PAGES << endl;
    cout << "Number of Frames: " << NUM_FRAMES << endl << endl;

    PageTable pt;

    int testAddresses[] = {0, 1024, 2048, 5120, 10240, 65535};

    for (int addr : testAddresses) {
        cout << "\n--- Translation Test ---\n";
        pt.translateAddress(addr);
    }

    pt.displayPageTable();

    char choice;
    cout << "\nEnter addresses interactively? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int addr;
        do {
            cout << "\nEnter logical address (-1 to quit): ";
            cin >> addr;
            if (addr >= 0) {
                pt.translateAddress(addr);
            }
        } while (addr >= 0);
    }

    return 0;
}
