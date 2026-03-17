#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{

    const char *file = "test.txt";

    if (access(file, R_OK) == 0)
        cout << "Read allowed\n";
    else
        cout << "Read denied\n";

    if (access(file, W_OK) == 0)
        cout << "Write allowed\n";
    else
        cout << "Write denied\n";

    return 0;
}