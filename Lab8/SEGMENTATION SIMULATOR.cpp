#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

struct SegmentTableEntry {
    int base;
    int limit;
    bool valid;
    string segmentName;

    SegmentTableEntry(int b = 0, int l = 0, bool v = false, string name = "")
        : base(b), limit(l), valid(v), segmentName(name) {}
};

class SegmentationSystem {
private:
    vector<SegmentTableEntry> segmentTable;
    static const int MAX_SEGMENTS = 8;
    int nextAvailableAddress;

public:
    SegmentationSystem() {
        segmentTable.resize(MAX_SEGMENTS);
        nextAvailableAddress = 0;
    }

    bool addSegment(int segmentNumber, int base, int limit, string name = "") {
        if (segmentNumber < 0 || segmentNumber >= MAX_SEGMENTS) {
            cout << "Error: Invalid segment number " << segmentNumber << endl;
            return false;
        }

        if (segmentTable[segmentNumber].valid) {
            cout << "Warning: Segment " << segmentNumber
                 << " already exists. Overwriting...\n";
        }

        segmentTable[segmentNumber] = SegmentTableEntry(base, limit, true, name);

        cout << "Segment " << segmentNumber << " (" << name << ") added\n";
        cout << "  Base : " << base << endl;
        cout << "  Limit: " << limit << endl;

        return true;
    }

    bool addSegmentAuto(int segmentNumber, int size, string name = "") {
        if (segmentNumber < 0 || segmentNumber >= MAX_SEGMENTS) {
            cout << "Error: Invalid segment number " << segmentNumber << endl;
            return false;
        }

        segmentTable[segmentNumber] =
            SegmentTableEntry(nextAvailableAddress, size, true, name);

        nextAvailableAddress += size;

        cout << "Segment " << segmentNumber << " (" << name << ") created\n";
        cout << "  Base : " << segmentTable[segmentNumber].base << endl;
        cout << "  Limit: " << size << endl;

        return true;
    }

    int translateAddress(int segmentNumber, int offset) {
        cout << "\n--- Address Translation ---\n";
        cout << "Logical Address: (Segment " << segmentNumber
             << ", Offset " << offset << ")\n";

        if (segmentNumber < 0 || segmentNumber >= MAX_SEGMENTS) {
            segmentationFault(segmentNumber, offset,
                              "Invalid segment number");
            return -1;
        }

        if (!segmentTable[segmentNumber].valid) {
            segmentationFault(segmentNumber, offset,
                              "Segment not in memory");
            return -1;
        }

        if (offset < 0 || offset >= segmentTable[segmentNumber].limit) {
            segmentationFault(segmentNumber, offset,
                              "Offset exceeds segment limit");
            return -1;
        }

        int physicalAddress =
            segmentTable[segmentNumber].base + offset;

        cout << "Segment Name   : "
             << segmentTable[segmentNumber].segmentName << endl;
        cout << "Base Address  : "
             << segmentTable[segmentNumber].base << endl;
        cout << "Limit         : "
             << segmentTable[segmentNumber].limit << endl;
        cout << "Physical Addr : "
             << physicalAddress << endl;
        cout << "Translation successful!\n";

        return physicalAddress;
    }

    void displaySegmentTable() {
        cout << "\n===== SEGMENT TABLE =====\n";
        cout << setw(8) << "Seg#"
             << setw(15) << "Name"
             << setw(10) << "Base"
             << setw(10) << "Limit"
             << setw(10) << "Valid" << endl;

        cout << string(53, '-') << endl;

        for (int i = 0; i < MAX_SEGMENTS; i++) {
            if (segmentTable[i].valid) {
                cout << setw(8) << i
                     << setw(15) << segmentTable[i].segmentName
                     << setw(10) << segmentTable[i].base
                     << setw(10) << segmentTable[i].limit
                     << setw(10) << "Yes" << endl;
            }
        }
    }

    void segmentationFault(int segment, int offset, const string& reason) {
        cout << "\n*** SEGMENTATION FAULT ***\n";
        cout << "Reason : " << reason << endl;
        cout << "Segment: " << segment << endl;
        cout << "Offset : " << offset << endl;

        if (segment >= 0 && segment < MAX_SEGMENTS &&
            segmentTable[segment].valid) {
            cout << "Segment Details:\n";
            cout << "  Name : " << segmentTable[segment].segmentName << endl;
            cout << "  Base : " << segmentTable[segment].base << endl;
            cout << "  Limit: " << segmentTable[segment].limit << endl;
            cout << "  Valid Offset Range: 0 - "
                 << segmentTable[segment].limit - 1 << endl;
        }
    }

    void displayMemoryLayout() {
        cout << "\n===== MEMORY LAYOUT =====\n";

        vector<pair<int, string>> layout;
        for (int i = 0; i < MAX_SEGMENTS; i++) {
            if (segmentTable[i].valid) {
                layout.push_back({
                    segmentTable[i].base,
                    "Segment " + to_string(i) +
                    " (" + segmentTable[i].segmentName + ")"
                });
            }
        }

        sort(layout.begin(), layout.end());

        for (const auto& item : layout) {
            cout << "Address " << setw(6) << item.first
                 << " : " << item.second << endl;
        }
    }
};

int main() {
    cout << "SEGMENTATION SYSTEM SIMULATOR\n";
    cout << "============================\n";

    SegmentationSystem segSys;

    cout << "\n--- Creating Program Segments ---\n";
    segSys.addSegmentAuto(0, 1000, "Code");
    segSys.addSegmentAuto(1, 400, "Global Data");
    segSys.addSegmentAuto(2, 300, "Heap");
    segSys.addSegmentAuto(3, 200, "Stack");
    segSys.addSegmentAuto(4, 500, "Shared Library");

    segSys.displaySegmentTable();
    segSys.displayMemoryLayout();

    cout << "\n--- Testing Address Translations ---\n";
    segSys.translateAddress(0, 500);
    segSys.translateAddress(1, 200);
    segSys.translateAddress(2, 150);

    segSys.translateAddress(0, 1500);
    segSys.translateAddress(5, 100);
    segSys.translateAddress(1, -50);

    char choice;
    cout << "\nTest custom addresses? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int seg, offset;
        do {
            cout << "\nEnter segment number (-1 to quit): ";
            cin >> seg;
            if (seg >= 0) {
                cout << "Enter offset: ";
                cin >> offset;
                segSys.translateAddress(seg, offset);
            }
        } while (seg >= 0);
    }

    return 0;
}
