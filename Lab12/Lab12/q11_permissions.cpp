#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

int main()
{

    ofstream f("secure.txt");
    f << "secret";
    f.close();

    chmod("secure.txt", 0600);

    struct stat info;

    stat("secure.txt", &info);

    cout << "Permission: " << oct << (info.st_mode & 0777) << endl;

    return 0;
}