#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{

    string filename;

    cout << "Enter filename: ";
    cin >> filename;

    if (access(filename.c_str(), R_OK) == 0)
        cout << "Readable\n";

    if (access(filename.c_str(), W_OK) == 0)
        cout << "Writable\n";

    if (access(filename.c_str(), X_OK) == 0)
        cout << "Executable\n";

    return 0;
}