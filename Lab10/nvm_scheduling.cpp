#include <iostream>
#include <queue>
using namespace std;

struct NVMRequest {
    int lba;        // Logical Block Address
    string type;    // "read" or "write"
};

void processNVMScheduling(queue<NVMRequest>& requestQueue)
{
    while (!requestQueue.empty())
    {
        NVMRequest r = requestQueue.front();
        requestQueue.pop();

        // NVMe has uniform access time (no seek)
        cout << r.type << " LBA " << r.lba
             << " -> latency: 0.1 ms" << endl;
    }
}

int main()
{
    queue<NVMRequest> q;
    q.push({100, "read"});
    q.push({5, "write"});
    q.push({999, "read"});

    processNVMScheduling(q);
    return 0;
}