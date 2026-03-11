#include <iostream>
#include <vector>
#include <string>
using namespace std;

class RAIDSystem
{
    int numDisks;
    vector<vector<string>> disks;

public:
    RAIDSystem(int n) : numDisks(n), disks(n) {}

    // RAID 0 - Striping
    void writeRAID0(const string& data)
    {
        for (int i = 0; i < data.size(); i++)
            disks[i % numDisks].push_back(string(1, data[i]));
    }

    // RAID 1 - Mirroring
    void writeRAID1(const string& data)
    {
        for (auto& disk : disks)
            disk.push_back(data);
    }

    void showStatus()
    {
        for (int i = 0; i < numDisks; i++)
        {
            cout << "Disk " << i << ": ";
            for (auto& b : disks[i])
                cout << b << " ";
            cout << endl;
        }
    }
};

int main()
{
    RAIDSystem raid0(3);
    raid0.writeRAID0("ABCDEF");
    cout << "=== RAID 0 ===" << endl;
    raid0.showStatus();

    RAIDSystem raid1(3);
    raid1.writeRAID1("BACKUP");
    cout << "=== RAID 1 ===" << endl;
    raid1.showStatus();

    return 0;
}