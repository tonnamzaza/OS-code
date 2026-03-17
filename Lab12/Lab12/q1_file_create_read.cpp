#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    ofstream outFile("data.txt");

    if (!outFile.is_open())
    {
        cout << "Cannot create file\n";
        return 1;
    }

    outFile << "Line 1: File Concept\n";
    outFile << "Line 2: Access Methods\n";
    outFile << "Line 3: Protection\n";

    outFile.close();

    ifstream inFile("data.txt");
    string line;

    cout << "File contents:\n";

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFile.close();

    return 0;
}