#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void traverse(const fs::path &path)
{

    for (auto &entry : fs::directory_iterator(path))
    {

        if (entry.is_directory())
        {
            cout << "[DIR] " << entry.path() << endl;
            traverse(entry.path());
        }
        else
        {
            cout << "[FILE] " << entry.path() << endl;
        }
    }
}

int main()
{

    traverse(".");

    return 0;
}