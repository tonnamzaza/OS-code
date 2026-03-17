#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{

    ifstream file("/proc/mounts");

    string line;

    while (getline(file, line))
    {

        istringstream iss(line);

        string device, mountpoint, type, options;
        int dump, pass;

        iss >> device >> mountpoint >> type >> options >> dump >> pass;

        cout << device << " "
             << mountpoint << " "
             << type << endl;
    }

    return 0;
}