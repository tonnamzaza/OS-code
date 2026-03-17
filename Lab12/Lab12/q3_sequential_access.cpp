#include <iostream>
#include <fstream>
using namespace std;

int main()
{

    ofstream out("records.bin", ios::binary);

    int numbers[5] = {100, 200, 300, 400, 500};

    for (int i = 0; i < 5; i++)
    {
        out.write((char *)&numbers[i], sizeof(int));
    }

    out.close();

    ifstream in("records.bin", ios::binary);

    int value;
    int index = 0;

    while (in.read((char *)&value, sizeof(int)))
    {
        cout << "Record[" << index << "] = " << value << endl;
        index++;
    }

    in.close();

    return 0;
}