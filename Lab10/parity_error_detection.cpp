#include <iostream>
#include <vector>
using namespace std;

int computeParityBit(const vector<int>& bits)
{
    int parity = 0;
    for (int b : bits)
        parity ^= b;
    return parity;
}

bool isParityCorrect(const vector<int>& data, int storedParity)
{
    return computeParityBit(data) == storedParity;
}

int main()
{
    vector<int> data = {1, 0, 1, 1, 0, 0, 1, 0};
    int parity = computeParityBit(data);

    cout << "Parity bit: " << parity << endl;

    // Simulate 1-bit error
    data[3] = 1 - data[3];

    cout << "Error detected: "
         << !isParityCorrect(data, parity) << endl;

    return 0;
}