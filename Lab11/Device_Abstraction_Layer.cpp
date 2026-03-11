#include <iostream>
using namespace std;

/* =========================
   Abstraction Layer
   ========================= */
class Device
{
public:
    virtual void open() = 0;
    virtual void read() = 0;
    virtual void write() = 0;
    virtual void close() = 0;

    virtual ~Device() {}
};

/* =========================
   Block Device (Disk)
   ========================= */
class DiskDevice : public Device
{
public:
    void open() override
    {
        cout << "Disk opened\n";
    }

    void read() override
    {
        cout << "Reading data from Disk\n";
    }

    void write() override
    {
        cout << "Writing data to Disk\n";
    }

    void close() override
    {
        cout << "Disk closed\n";
    }
};

/* =========================
   Character Device (Keyboard)
   ========================= */
class KeyboardDevice : public Device
{
public:
    void open() override
    {
        cout << "Keyboard connected\n";
    }

    void read() override
    {
        cout << "Reading input from Keyboard\n";
    }

    void write() override
    {
        cout << "Keyboard cannot write data\n";
    }

    void close() override
    {
        cout << "Keyboard disconnected\n";
    }
};

/* =========================
   Output Device (Printer)
   ========================= */
class PrinterDevice : public Device
{
public:
    void open() override
    {
        cout << "Printer ready\n";
    }

    void read() override
    {
        cout << "Printer cannot read data\n";
    }

    void write() override
    {
        cout << "Printing document\n";
    }

    void close() override
    {
        cout << "Printer offline\n";
    }
};

/* =========================
   Main Program
   ========================= */
int main()
{
    Device *devices[3];

    devices[0] = new DiskDevice();
    devices[1] = new KeyboardDevice();
    devices[2] = new PrinterDevice();

    for (int i = 0; i < 3; i++)
    {
        cout << "\n--- Device " << i + 1 << " ---\n";
        devices[i]->open();
        devices[i]->read();
        devices[i]->write();
        devices[i]->close();
    }

    for (int i = 0; i < 3; i++)
    {
        delete devices[i];
    }

    return 0;
}
