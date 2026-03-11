#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

/* =========================
   I/O Request
   ========================= */
struct IORequest
{
    int processId;
    int blockNumber;
};

/* =========================
   I/O Scheduler (FIFO)
   ========================= */
class IOScheduler
{
private:
    queue<IORequest> requestQueue;

public:
    void addRequest(int pid, int block)
    {
        requestQueue.push({pid, block});
    }

    bool hasRequest()
    {
        return !requestQueue.empty();
    }

    IORequest getNextRequest()
    {
        IORequest r = requestQueue.front();
        requestQueue.pop();
        return r;
    }
};

/* =========================
   Cache Simulation
   ========================= */
class Cache
{
private:
    unordered_map<int, int> cache; // block -> data

public:
    bool hasBlock(int block)
    {
        return cache.find(block) != cache.end();
    }

    int readBlock(int block)
    {
        return cache[block];
    }

    void writeBlock(int block, int data)
    {
        cache[block] = data;
    }
};

/* =========================
   Buffering Simulation
   ========================= */
class Buffer
{
private:
    vector<int> buffer;
    int size;
    int index;

public:
    Buffer(int s) : size(s), index(0)
    {
        buffer.resize(size, -1);
    }

    void write(int data)
    {
        buffer[index] = data;
        index = (index + 1) % size; // circular
    }

    void display()
    {
        cout << "Buffer: ";
        for (int d : buffer)
            cout << d << " ";
        cout << endl;
    }
};

/* =========================
   Kernel I/O Subsystem
   ========================= */
class KernelIO
{
private:
    IOScheduler scheduler;
    Cache cache;
    Buffer buffer;

public:
    KernelIO() : buffer(3) {} // circular buffer size = 3

    void requestIO(int pid, int block)
    {
        scheduler.addRequest(pid, block);
    }

    void processIO()
    {
        while (scheduler.hasRequest())
        {
            IORequest req = scheduler.getNextRequest();
            cout << "\nProcess " << req.processId
                 << " requests block " << req.blockNumber << endl;

            // Check cache
            if (cache.hasBlock(req.blockNumber))
            {
                cout << "Cache hit!\n";
                buffer.write(cache.readBlock(req.blockNumber));
            }
            else
            {
                cout << "Cache miss! Reading from disk...\n";
                int data = req.blockNumber * 10; // fake disk data
                cache.writeBlock(req.blockNumber, data);
                buffer.write(data);
            }

            buffer.display();
        }
    }
};

/* =========================
   Main Program
   ========================= */
int main()
{
    KernelIO kernel;

    kernel.requestIO(1, 5);
    kernel.requestIO(2, 3);
    kernel.requestIO(3, 5); // cache hit
    kernel.requestIO(4, 7);

    kernel.processIO();

    return 0;
}
