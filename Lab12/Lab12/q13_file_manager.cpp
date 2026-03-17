#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void listDir()
{

    for (auto &entry : fs::directory_iterator("."))
    {

        cout << entry.path().filename() << " ";

        if (entry.is_regular_file())
            cout << entry.file_size() << " bytes";

        cout << endl;
    }
}

void copyFile(string src, string dst)
{

    try
    {
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        cout << "Copied\n";
    }
    catch (...)
    {
        cout << "Copy failed\n";
    }
}

int main()
{

    cout << "Directory:\n";
    listDir();

    ofstream("a.txt") << "hello";

    copyFile("a.txt", "a_copy.txt");

    return 0;
}