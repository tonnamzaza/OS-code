#include <iostream>
#include <vector>
using namespace std;

class PageTableEntry {
private:
    int frameNumber;
    bool valid;
    bool dirty;
    bool referenced;

public:
    PageTableEntry() {
        frameNumber = -1;
        valid = false;
        dirty = false;
        referenced = false;
    }

    void setEntry(int frame) {
        frameNumber = frame;
        valid = true;
        referenced = true;
    }

    int getFrameNumber() const {
        return frameNumber;
    }

    bool isValid() const {
        return valid;
    }

    void display(int pageNumber) const {
        cout << "Page " << pageNumber
             << " | Frame: " << frameNumber
             << " | Valid: " << valid
             << " | Dirty: " << dirty
             << " | Referenced: " << referenced << endl;
    }
};

class PageTable {
private:
    vector<PageTableEntry> table;
    int pageSize;

public:
    PageTable(int numPages, int pSize) {
        pageSize = pSize;
        table.resize(numPages);

        // ตั้งค่า page ตัวอย่าง
        table[0].setEntry(5);
        table[1].setEntry(3);
        table[2].setEntry(4);
    }

    void translateAddress(int virtualAddress) {
        int pageNumber = virtualAddress / pageSize;
        int offset = virtualAddress % pageSize;

        cout << "Virtual Address: " << virtualAddress << endl;
        cout << "Page Number: " << pageNumber
             << ", Offset: " << offset << endl;

        if (pageNumber >= table.size() || !table[pageNumber].isValid()) {
            cout << "Page Fault!" << endl;
            return;
        }

        int physicalAddress =
            table[pageNumber].getFrameNumber() * pageSize + offset;

        cout << "Physical Address: " << physicalAddress << endl;
    }

    void displayPageTable() {
        cout << "\nCurrent Page Table\n";
        for (int i = 0; i < table.size(); i++) {
            table[i].display(i);
        }
    }
};

int main() {
    const int PAGE_SIZE = 1024;
    PageTable pt(4, PAGE_SIZE);

    int virtualAddress = 1024;
    pt.translateAddress(virtualAddress);

    pt.displayPageTable();

    return 0;
}