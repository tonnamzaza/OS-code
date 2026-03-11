#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/* =======================
   Class IOPort
   ======================= */
class IOPort
{
private:
    unsigned char dataRegister; // 8-bit data register
    bool busy;
    bool error;
    bool ready;
    bool interruptEnabled;

public:
    IOPort()
    {
        dataRegister = 0;
        busy = false;
        error = false;
        ready = true;
        interruptEnabled = false;
    }

    // Control Register
    void enableInterrupt(bool enable)
    {
        interruptEnabled = enable;
    }

    // Write data
    void writeData(unsigned char data)
    {
        if (busy)
        {
            error = true;
            return;
        }
        busy = true;
        ready = false;
        dataRegister = data;
    }

    // Simulate device processing
    void process()
    {
        this_thread::sleep_for(chrono::seconds(2));
        busy = false;
        ready = true;
    }

    // Status Register
    bool isBusy() const { return busy; }
    bool isReady() const { return ready; }
    bool hasError() const { return error; }
    bool isInterruptEnabled() const { return interruptEnabled; }

    unsigned char readData() const
    {
        return dataRegister;
    }
};

/* =======================
   Class DeviceController
   ======================= */
class DeviceController
{
private:
    IOPort &port;

public:
    DeviceController(IOPort &p) : port(p) {}

    // Polling I/O
    void pollingIO(unsigned char data)
    {
        cout << "[Polling] Writing data...\n";
        port.writeData(data);

        while (port.isBusy())
        {
            cout << "[Polling] Device busy...\n";
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        cout << "[Polling] Done. Data = "
             << (int)port.readData() << endl;
    }

    // Interrupt-driven I/O
    void interruptIO(unsigned char data)
    {
        cout << "[Interrupt] Writing data...\n";
        port.enableInterrupt(true);
        port.writeData(data);

        // Simulate interrupt
        thread deviceThread([&]()
                            {
            port.process();
            if (port.isInterruptEnabled()) {
                cout << "[Interrupt] Device finished! Interrupt received.\n";
                cout << "[Interrupt] Data = "
                     << (int)port.readData() << endl;
            } });

        deviceThread.join();
    }
};

/* =======================
   Main Program
   ======================= */
int main()
{
    IOPort port;
    DeviceController controller(port);

    cout << "=== Polling I/O Simulation ===\n";
    controller.pollingIO(100);

    cout << "\n=== Interrupt-driven I/O Simulation ===\n";
    controller.interruptIO(200);

    return 0;
}
