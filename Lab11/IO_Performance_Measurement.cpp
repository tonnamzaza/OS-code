#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

/* =========================
   Programmed I/O Simulation
   ========================= */
void programmedIO(int operations)
{
    for (int i = 0; i < operations; i++)
    {
        // CPU busy waiting
        this_thread::sleep_for(milliseconds(50));
    }
}

/* =========================
   DMA I/O Simulation
   ========================= */
void dmaIO(int operations)
{
    // CPU setup DMA
    this_thread::sleep_for(milliseconds(100));

    // DMA works independently
    this_thread::sleep_for(milliseconds(20 * operations));
}

/* =========================
   Main Program
   ========================= */
int main()
{
    int operations = 10;

    cout << "=== I/O Performance Measurement ===\n";
    cout << "Operations: " << operations << "\n\n";

    // Measure Programmed I/O
    auto start1 = high_resolution_clock::now();
    programmedIO(operations);
    auto end1 = high_resolution_clock::now();

    auto programmedTime =
        duration_cast<milliseconds>(end1 - start1).count();

    // Measure DMA I/O
    auto start2 = high_resolution_clock::now();
    dmaIO(operations);
    auto end2 = high_resolution_clock::now();

    auto dmaTime =
        duration_cast<milliseconds>(end2 - start2).count();

    // Calculate throughput
    double progThroughput = operations / (programmedTime / 1000.0);
    double dmaThroughput = operations / (dmaTime / 1000.0);

    cout << "Programmed I/O Time : " << programmedTime << " ms\n";
    cout << "DMA I/O Time        : " << dmaTime << " ms\n\n";

    cout << "Programmed I/O Throughput : "
         << progThroughput << " ops/sec\n";
    cout << "DMA I/O Throughput        : "
         << dmaThroughput << " ops/sec\n";

    return 0;
}
