#include <iostream>
#include <map>
#include <list>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MIN_BLOCK_SIZE = 1;    // 1 KB
const int MAX_BLOCK_SIZE = 1024; // 1024 KB

struct Block {
    int address;
    int size;
    bool isFree;
    int allocID;

    Block(int addr, int s, bool free = true, int id = -1)
        : address(addr), size(s), isFree(free), allocID(id) {}
};

class BuddySystem {
private:
    map<int, list<Block*>> freeLists;
    list<Block*> allBlocks;
    int nextAllocID;

    int nextPowerOf2(int size) {
        int power = 1;
        while (power < size)
            power *= 2;
        return min(power, MAX_BLOCK_SIZE);
    }

    int findBuddy(int address, int size) {
        return address ^ size;
    }

    void splitBlock(int size) {
        int largerSize = size * 2;
        while (largerSize <= MAX_BLOCK_SIZE) {
            if (!freeLists[largerSize].empty()) {
                Block* block = freeLists[largerSize].front();
                freeLists[largerSize].pop_front();

                cout << "Splitting block size " << largerSize
                     << " at address " << block->address << endl;

                int half = largerSize / 2;
                Block* b1 = new Block(block->address, half, true);
                Block* b2 = new Block(block->address + half, half, true);

                freeLists[half].push_back(b1);
                freeLists[half].push_back(b2);
                allBlocks.push_back(b1);
                allBlocks.push_back(b2);

                allBlocks.remove(block);
                delete block;

                if (half > size)
                    splitBlock(size);
                return;
            }
            largerSize *= 2;
        }
    }

public:
    BuddySystem() : nextAllocID(1) {
        Block* initial = new Block(0, MAX_BLOCK_SIZE, true);
        freeLists[MAX_BLOCK_SIZE].push_back(initial);
        allBlocks.push_back(initial);

        cout << "Buddy System initialized with "
             << MAX_BLOCK_SIZE << " KB\n";
    }

    ~BuddySystem() {
        for (Block* b : allBlocks)
            delete b;
    }

    Block* allocate(int requestSize) {
        cout << "\n--- Allocation Request ---\n";
        cout << "Requested size : " << requestSize << " KB\n";

        int size = nextPowerOf2(requestSize);
        cout << "Rounded to     : " << size << " KB\n";

        if (freeLists[size].empty()) {
            cout << "No block of size " << size
                 << " KB, splitting...\n";
            splitBlock(size);
        }

        if (freeLists[size].empty()) {
            cout << "Allocation FAILED\n";
            return nullptr;
        }

        Block* block = freeLists[size].front();
        freeLists[size].pop_front();

        block->isFree = false;
        block->allocID = nextAllocID++;

        cout << "Allocated block #" << block->allocID
             << " at address " << block->address
             << " (" << block->size << " KB)\n";

        cout << "Internal fragmentation : "
             << (size - requestSize) << " KB\n";

        return block;
    }

    void deallocate(Block* block) {
        if (!block) return;

        cout << "\n--- Deallocation ---\n";
        cout << "Freeing block #" << block->allocID
             << " at address " << block->address << endl;

        block->isFree = true;
        block->allocID = -1;
        coalesce(block);
    }

    void coalesce(Block* block) {
        int buddyAddr = findBuddy(block->address, block->size);

        Block* buddy = nullptr;
        for (Block* b : freeLists[block->size]) {
            if (b->address == buddyAddr && b->isFree) {
                buddy = b;
                break;
            }
        }

        if (buddy && block->size * 2 <= MAX_BLOCK_SIZE) {
            freeLists[block->size].remove(block);
            freeLists[block->size].remove(buddy);

            int newAddr = min(block->address, buddy->address);
            int newSize = block->size * 2;

            Block* merged = new Block(newAddr, newSize, true);
            freeLists[newSize].push_back(merged);
            allBlocks.push_back(merged);

            allBlocks.remove(block);
            allBlocks.remove(buddy);
            delete block;
            delete buddy;

            coalesce(merged);
        } else {
            freeLists[block->size].push_back(block);
        }
    }

    void displayFreeLists() {
        cout << "\n===== FREE LISTS =====\n";
        for (int s = MIN_BLOCK_SIZE; s <= MAX_BLOCK_SIZE; s *= 2) {
            cout << setw(6) << s << " KB : ";
            cout << freeLists[s].size() << " block(s)\n";
        }
    }

    void displayAllBlocks() {
        cout << "\n===== ALL BLOCKS =====\n";
        cout << setw(8) << "Addr"
             << setw(8) << "Size"
             << setw(8) << "State"
             << setw(8) << "ID\n";

        list<Block*> sorted = allBlocks;
        sorted.sort([](Block* a, Block* b) {
            return a->address < b->address;
        });

        for (Block* b : sorted) {
            cout << setw(8) << b->address
                 << setw(8) << b->size
                 << setw(8) << (b->isFree ? "FREE" : "USED")
                 << setw(8) << (b->isFree ? "-" : to_string(b->allocID))
                 << endl;
        }
    }

    void displayStats() {
        int used = 0, free = 0;
        for (Block* b : allBlocks) {
            if (b->isFree) free += b->size;
            else used += b->size;
        }

        cout << "\n===== STATISTICS =====\n";
        cout << "Total Memory : " << MAX_BLOCK_SIZE << " KB\n";
        cout << "Used Memory  : " << used << " KB\n";
        cout << "Free Memory  : " << free << " KB\n";

        double util = (double)used / MAX_BLOCK_SIZE * 100;
        cout << fixed << setprecision(2);
        cout << "Utilization  : " << util << " %\n";
    }
};

int main() {
    cout << "BUDDY SYSTEM MEMORY ALLOCATOR\n";
    cout << "============================\n\n";

    BuddySystem buddy;

    Block* b1 = buddy.allocate(100);
    buddy.displayFreeLists();

    Block* b2 = buddy.allocate(240);
    buddy.displayFreeLists();

    Block* b3 = buddy.allocate(64);
    buddy.displayFreeLists();

    Block* b4 = buddy.allocate(256);
    buddy.displayFreeLists();

    buddy.displayAllBlocks();
    buddy.displayStats();

    cout << "\n--- DEALLOCATION & COALESCING ---\n";
    buddy.deallocate(b1);
    buddy.deallocate(b3);
    buddy.deallocate(b2);
    buddy.deallocate(b4);

    buddy.displayFreeLists();
    buddy.displayAllBlocks();
    buddy.displayStats();

    return 0;
}
