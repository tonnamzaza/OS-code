#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main()
{

    ofstream f("original.txt");
    f << "Hello";
    f.close();

    link("original.txt", "hardlink.txt");

    symlink("original.txt", "symlink.txt");

    unlink("original.txt");

    ifstream test("hardlink.txt");

    if (test.good())
        cout << "Hardlink works\n";

    ifstream test2("symlink.txt");

    if (!test2.good())
        cout << "Symlink broken\n";

    return 0;
}