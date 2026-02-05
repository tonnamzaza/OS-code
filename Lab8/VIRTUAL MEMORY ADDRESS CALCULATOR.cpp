#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

class VirtualMemoryCalculator {
private:
    long long addressSpaceBits;
    long long pageSize;
    long long physicalMemorySize;
    long long pageTableEntrySize;

    long long power(long long base, int exp) {
        long long result = 1;
        for (int i = 0; i < exp; i++)
            result *= base;
        return result;
    }

    int log2ll(long long n) {
        int count = 0;
        while (n > 1) {
            n /= 2;
            count++;
        }
        return count;
    }

    string formatBytes(long long bytes) {
        if (bytes >= 1099511627776LL)
            return to_string(bytes / 1099511627776LL) + " TB";
        else if (bytes >= 1073741824LL)
            return to_string(bytes / 1073741824LL) + " GB";
        else if (bytes >= 1048576LL)
            return to_string(bytes / 1048576LL) + " MB";
        else if (bytes >= 1024LL)
            return to_string(bytes / 1024LL) + " KB";
        return to_string(bytes) + " bytes";
    }

public:
    void calculateBasicPaging() {
        cout << "\n===== BASIC PAGING CALCULATOR =====\n";
        cout << "Enter virtual address space bits: ";
        cin >> addressSpaceBits;
        cout << "Enter page size (bytes): ";
        cin >> pageSize;

        int offsetBits = log2ll(pageSize);
        int pageNumberBits = addressSpaceBits - offsetBits;
        long long numPages = power(2, pageNumberBits);
        long long addressSpaceSize = power(2, addressSpaceBits);

        cout << "\n=== RESULTS ===\n";
        cout << "Virtual Address Space : " << formatBytes(addressSpaceSize) << endl;
        cout << "Page Size             : " << formatBytes(pageSize) << endl;
        cout << "Number of Pages       : " << numPages << endl;
        cout << "Offset Bits           : " << offsetBits << endl;
        cout << "Page Number Bits      : " << pageNumberBits << endl;

        cout << "\nEnter page table entry size (bytes): ";
        cin >> pageTableEntrySize;

        long long pageTableSize = numPages * pageTableEntrySize;
        cout << "Page Table Size       : " << formatBytes(pageTableSize) << endl;
    }

    void calculateTwoLevelPaging() {
        cout << "\n===== TWO-LEVEL PAGING CALCULATOR =====\n";
        cout << "Enter virtual address space bits: ";
        cin >> addressSpaceBits;
        cout << "Enter page size (bytes): ";
        cin >> pageSize;
        cout << "Enter page table entry size (bytes): ";
        cin >> pageTableEntrySize;

        int offsetBits = log2ll(pageSize);
        long long ptesPerPage = pageSize / pageTableEntrySize;
        int secondLevelBits = log2ll(ptesPerPage);
        int firstLevelBits = addressSpaceBits - offsetBits - secondLevelBits;

        long long outerSize = power(2, firstLevelBits) * pageTableEntrySize;
        long long maxInnerSize = power(2, firstLevelBits) * pageSize;

        cout << "\n=== RESULTS ===\n";
        cout << "Offset Bits           : " << offsetBits << endl;
        cout << "Outer Index Bits      : " << firstLevelBits << endl;
        cout << "Inner Index Bits      : " << secondLevelBits << endl;
        cout << "Outer Page Table Size : " << formatBytes(outerSize) << endl;
        cout << "Max Inner Tables Size : " << formatBytes(maxInnerSize) << endl;
    }

    void calculatePhysicalMemory() {
        cout << "\n===== PHYSICAL MEMORY CALCULATOR =====\n";
        int physicalAddressBits;
        cout << "Enter physical address bits: ";
        cin >> physicalAddressBits;
        cout << "Enter frame size (bytes): ";
        cin >> pageSize;

        int offsetBits = log2ll(pageSize);
        int frameBits = physicalAddressBits - offsetBits;

        long long frames = power(2, frameBits);
        long long memorySize = power(2, physicalAddressBits);

        cout << "\n=== RESULTS ===\n";
        cout << "Physical Memory Size : " << formatBytes(memorySize) << endl;
        cout << "Frame Size           : " << formatBytes(pageSize) << endl;
        cout << "Number of Frames     : " << frames << endl;
    }

    void calculateEffectiveAccessTime() {
        cout << "\n===== EFFECTIVE ACCESS TIME =====\n";
        double mem, tlb, hit;
        cout << "Memory access time (ns): ";
        cin >> mem;
        cout << "TLB access time (ns): ";
        cin >> tlb;
        cout << "TLB hit ratio (0-1): ";
        cin >> hit;

        double eat = hit * (tlb + mem) + (1 - hit) * (tlb + 2 * mem);
        double slowdown = eat / mem;

        cout << fixed << setprecision(2);
        cout << "\nEffective Access Time : " << eat << " ns\n";
        cout << "Slowdown Factor       : " << slowdown << "x\n";
        cout << "Performance Overhead  : " << (slowdown - 1) * 100 << " %\n";
    }

    void addressExample() {
        cout << "\n===== ADDRESS TRANSLATION EXAMPLE =====\n";
        cout << "Enter address space bits: ";
        cin >> addressSpaceBits;
        cout << "Enter page size (bytes): ";
        cin >> pageSize;

        long long logical;
        cout << "Enter logical address (decimal): ";
        cin >> logical;

        long long page = logical / pageSize;
        long long offset = logical % pageSize;

        cout << "Page Number : " << page << endl;
        cout << "Offset      : " << offset << endl;

        long long frame;
        cout << "Enter frame number: ";
        cin >> frame;

        long long physical = frame * pageSize + offset;
        cout << "Physical Address : " << physical << endl;
    }

    void mainMenu() {
        int choice;
        do {
            cout << "\n===== VIRTUAL MEMORY CALCULATOR =====\n";
            cout << "1. Basic Paging\n";
            cout << "2. Two-Level Paging\n";
            cout << "3. Physical Memory\n";
            cout << "4. Effective Access Time\n";
            cout << "5. Address Translation Example\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: calculateBasicPaging(); break;
                case 2: calculateTwoLevelPaging(); break;
                case 3: calculatePhysicalMemory(); break;
                case 4: calculateEffectiveAccessTime(); break;
                case 5: addressExample(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    VirtualMemoryCalculator calc;
    calc.mainMenu();
    return 0;
}
