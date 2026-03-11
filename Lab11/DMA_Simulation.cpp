#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

/* =========================
   Programmed I/O Simulation
   ========================= */
void programmedIO(vector<int>& memory, vector<int>& device) {
    cout << "=== Programmed I/O ===\n";
    for (size_t i = 0; i < device.size(); i++) {
        cout << "CPU transferring data: " << device[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // CPU busy
        memory.push_back(device[i]);
    }
    cout << "Programmed I/O finished\n\n";
}

/* =========================
   DMA Controller Simulation
   ========================= */
class DMAController {
public:
    void transfer(vector<int>& memory, vector<int>& device) {
        cout << "=== DMA Transfer Started ===\n";

        // Simulate DMA working independently
        this_thread::sleep_for(chrono::seconds(2));

        for (int data : device) {
            memory.push_back(data);
        }

        cout << "=== DMA Transfer Completed (Interrupt CPU) ===\n\n";
    }
};

int main() {
    vector<int> mainMemory;
    vector<int> deviceBuffer = {10, 20, 30, 40, 50};

    // Programmed I/O
    programmedIO(mainMemory, deviceBuffer);

    cout << "Memory after Programmed I/O: ";
    for (int d : mainMemory) cout << d << " ";
    cout << "\n\n";

    // Clear memory
    mainMemory.clear();

    // DMA I/O
    DMAController dma;
    cout << "CPU starts DMA and does other work...\n";
    dma.transfer(mainMemory, deviceBuffer);

    cout << "Memory after DMA: ";
    for (int d : mainMemory) cout << d << " ";
    cout << endl;

    return 0;
}
