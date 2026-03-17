#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main()
{

    for (auto &entry : fs::directory_iterator("."))
    {

        if (entry.is_directory())
        {
            cout << "[DIR] " << entry.path().filename() << endl;
        }
        else if (entry.is_regular_file())
        {
            cout << "[FILE] " << entry.path().filename()
                 << " " << entry.file_size() << " bytes\n";
        }
    }

    return 0;
}