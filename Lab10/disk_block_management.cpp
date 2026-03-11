#include <iostream>
#include <bitset>
using namespace std;

const int TOTAL_BLOCKS = 16;

class DiskManager
{
    bitset<TOTAL_BLOCKS> freeBlocks;

public:
    DiskManager()
    {
        freeBlocks.set(); // all blocks free
    }

    int allocateBlock()
    {
        for (int i = 0; i < TOTAL_BLOCKS; i++)
        {
            if (freeBlocks[i])
            {
                freeBlocks[i] = 0;
                return i;
            }
        }
        return -1; // disk full
    }

    void releaseBlock(int block)
    {
        freeBlocks[block] = 1;
    }

    void showStatus()
    {
        cout << "Free blocks: "
             << freeBlocks.count()
             << "/" << TOTAL_BLOCKS << endl;
    }
};

int main()
{
    DiskManager dm;

    int b1 = dm.allocateBlock();
    int b2 = dm.allocateBlock();

    dm.showStatus();
    dm.releaseBlock(b1);
    dm.showStatus();

    return 0;
}