#include <iostream>
#include <map>
using namespace std;

map<int, bool> memory; // size -> free/used

void allocate(int size) {
    int block = 1024;
    while (block / 2 >= size)
        block /= 2;

    if (!memory[block]) {
        memory[block] = true;
        cout << "Allocated " << block << " KB\n";
    } else {
        cout << "Block not available\n";
    }
}

void deallocate(int size) {
    memory[size] = false;
    cout << "Deallocated " << size << " KB\n";
}

int main() {
    memory[1024] = false;

    allocate(70);
    allocate(35);
    allocate(80);
    deallocate(128);

    return 0;
}