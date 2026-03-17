#include <iostream>
#include <sys/stat.h>
#include <ctime>
using namespace std;

int main()
{

    struct stat fileInfo;

    const char *filename = "data.txt";

    if (stat(filename, &fileInfo) != 0)
    {
        cout << "Cannot read file info\n";
        return 1;
    }

    cout << "File: " << filename << endl;
    cout << "Size: " << fileInfo.st_size << " bytes\n";

    cout << "Last Modified: " << ctime(&fileInfo.st_mtime);

    cout << "Is Regular File: ";

    if (S_ISREG(fileInfo.st_mode))
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}