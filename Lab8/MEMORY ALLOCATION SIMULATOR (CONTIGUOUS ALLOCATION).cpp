#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct MemoryBlock
{
    int startAddress;
    int size;
    bool isFree;
    int processID;

    MemoryBlock(int start, int s, bool free = true, int pid = -1)
        : startAddress(start), size(s), isFree(free), processID(pid) {}
};

class MemoryManager
{
private:
    vector<MemoryBlock> blocks;
    const int TOTAL_MEMORY = 1048576; // 1 MB

    void mergeAdjacentFreeBlocks()
    {
        for (size_t i = 0; i + 1 < blocks.size();)
        {
            if (blocks[i].isFree && blocks[i + 1].isFree)
            {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }
            else
            {
                i++;
            }
        }
    }

public:
    MemoryManager()
    {
        blocks.push_back(MemoryBlock(0, TOTAL_MEMORY, true));
    }

    bool allocateFirstFit(int processID, int size)
    {
        cout << "\n--- First-Fit Allocation ---\n";
        cout << "Process " << processID << " requests "
             << size << " bytes\n";

        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= size)
            {
                cout << "Found free block at address "
                     << blocks[i].startAddress
                     << " with size " << blocks[i].size << endl;

                if (blocks[i].size > size)
                {
                    int newStart = blocks[i].startAddress + size;
                    int newSize = blocks[i].size - size;

                    blocks[i].size = size;
                    blocks[i].isFree = false;
                    blocks[i].processID = processID;

                    blocks.insert(blocks.begin() + i + 1,
                                  MemoryBlock(newStart, newSize, true));
                }
                else
                {
                    blocks[i].isFree = false;
                    blocks[i].processID = processID;
                }

                cout << "Allocated at address "
                     << blocks[i].startAddress << endl;
                return true;
            }
        }

        cout << "Allocation FAILED\n";
        return false;
    }

    bool allocateBestFit(int processID, int size)
    {
        cout << "\n--- Best-Fit Allocation ---\n";
        cout << "Process " << processID << " requests "
             << size << " bytes\n";

        int bestIndex = -1;
        int bestSize = TOTAL_MEMORY + 1;

        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= size)
            {
                if (blocks[i].size < bestSize)
                {
                    bestSize = blocks[i].size;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex == -1)
        {
            cout << "Allocation FAILED\n";
            return false;
        }

        if (blocks[bestIndex].size > size)
        {
            int newStart = blocks[bestIndex].startAddress + size;
            int newSize = blocks[bestIndex].size - size;

            blocks[bestIndex].size = size;
            blocks[bestIndex].isFree = false;
            blocks[bestIndex].processID = processID;

            blocks.insert(blocks.begin() + bestIndex + 1,
                          MemoryBlock(newStart, newSize, true));
        }
        else
        {
            blocks[bestIndex].isFree = false;
            blocks[bestIndex].processID = processID;
        }

        cout << "Allocated at address "
             << blocks[bestIndex].startAddress << endl;
        return true;
    }

    bool allocateWorstFit(int processID, int size)
    {
        cout << "\n--- Worst-Fit Allocation ---\n";
        cout << "Process " << processID << " requests "
             << size << " bytes\n";

        int worstIndex = -1;
        int worstSize = -1;

        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= size)
            {
                if (blocks[i].size > worstSize)
                {
                    worstSize = blocks[i].size;
                    worstIndex = i;
                }
            }
        }

        if (worstIndex == -1)
        {
            cout << "Allocation FAILED\n";
            return false;
        }

        if (blocks[worstIndex].size > size)
        {
            int newStart = blocks[worstIndex].startAddress + size;
            int newSize = blocks[worstIndex].size - size;

            blocks[worstIndex].size = size;
            blocks[worstIndex].isFree = false;
            blocks[worstIndex].processID = processID;

            blocks.insert(blocks.begin() + worstIndex + 1,
                          MemoryBlock(newStart, newSize, true));
        }
        else
        {
            blocks[worstIndex].isFree = false;
            blocks[worstIndex].processID = processID;
        }

        cout << "Allocated at address "
             << blocks[worstIndex].startAddress << endl;
        return true;
    }

    void deallocate(int processID)
    {
        cout << "\n--- Deallocation ---\n";
        bool found = false;

        for (auto &block : blocks)
        {
            if (!block.isFree && block.processID == processID)
            {
                block.isFree = true;
                block.processID = -1;
                found = true;
            }
        }

        if (!found)
        {
            cout << "Process not found\n";
            return;
        }

        mergeAdjacentFreeBlocks();
        cout << "Memory freed and merged\n";
    }

    void displayMemory()
    {
        cout << "\n===== MEMORY MAP =====\n";
        cout << setw(12) << "Start"
             << setw(10) << "Size"
             << setw(10) << "Status"
             << setw(12) << "PID" << endl;
        cout << string(44, '-') << endl;

        for (const auto &b : blocks)
        {
            cout << setw(12) << b.startAddress
                 << setw(10) << b.size
                 << setw(10) << (b.isFree ? "FREE" : "USED")
                 << setw(12) << (b.isFree ? "-" : to_string(b.processID))
                 << endl;
        }
    }

    void calculateFragmentation()
    {
        int totalFree = 0, largestFree = 0;

        for (const auto &b : blocks)
        {
            if (b.isFree)
            {
                totalFree += b.size;
                largestFree = max(largestFree, b.size);
            }
        }

        int externalFrag = totalFree - largestFree;
        double percent = (totalFree > 0)
                             ? (double)externalFrag / totalFree * 100
                             : 0;

        cout << "\n===== FRAGMENTATION =====\n";
        cout << "Total Free Space     : " << totalFree << " bytes\n";
        cout << "Largest Free Block  : " << largestFree << " bytes\n";
        cout << "External Fragment   : " << externalFrag << " bytes\n";
        cout << fixed << setprecision(2);
        cout << "Fragmentation (%)   : " << percent << "%\n";
    }
};

int main()
{
    cout << "MEMORY ALLOCATION SIMULATOR\n";
    cout << "===========================\n";

    // First Fit
    MemoryManager mm;
    mm.allocateFirstFit(1, 200000);
    mm.allocateFirstFit(2, 150000);
    mm.allocateFirstFit(3, 300000);
    mm.displayMemory();
    mm.deallocate(2);
    mm.allocateFirstFit(4, 100000);
    mm.displayMemory();
    mm.calculateFragmentation();

    // Best Fit
    MemoryManager mm2;
    mm2.allocateBestFit(1, 200000);
    mm2.allocateBestFit(2, 150000);
    mm2.allocateBestFit(3, 300000);
    mm2.deallocate(2);
    mm2.allocateBestFit(4, 100000);
    mm2.displayMemory();
    mm2.calculateFragmentation();

    // Worst Fit
    MemoryManager mm3;
    mm3.allocateWorstFit(1, 200000);
    mm3.allocateWorstFit(2, 150000);
    mm3.allocateWorstFit(3, 300000);
    mm3.deallocate(2);
    mm3.allocateWorstFit(4, 100000);
    mm3.displayMemory();
    mm3.calculateFragmentation();

    return 0;
}
