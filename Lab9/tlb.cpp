#include <iostream>
#include <vector>
using namespace std;

struct TLBEntry {
    int page;
    int lastUsed;
};

int main() {
    vector<int> reference =
        {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0};

    const int TLB_SIZE = 4;
    vector<TLBEntry> tlb;

    int time = 0, hit = 0, miss = 0;

    for (int page : reference) {
        time++;
        bool found = false;

        for (auto &e : tlb) {
            if (e.page == page) {
                e.lastUsed = time;
                hit++;
                found = true;
                break;
            }
        }

        if (!found) {
            miss++;
            if (tlb.size() < TLB_SIZE) {
                tlb.push_back({page, time});
            } else {
                int lru = 0;
                for (int i = 1; i < tlb.size(); i++)
                    if (tlb[i].lastUsed < tlb[lru].lastUsed)
                        lru = i;
                tlb[lru] = {page, time};
            }
        }
    }

    double hitRatio = (double)hit / reference.size();
    double missRatio = 1 - hitRatio;

    double EMAT =
        hitRatio * 20 +
        missRatio * (20 + 100);

    cout << "TLB Hits: " << hit << endl;
    cout << "TLB Misses: " << miss << endl;
    cout << "Hit Ratio: " << hitRatio << endl;
    cout << "Effective Memory Access Time: " << EMAT << " ns\n";

    return 0;
}