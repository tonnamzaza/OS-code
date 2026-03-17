#include <iostream>
#include <fstream>
using namespace std;

struct Record
{
    int id;
    char name[20];
    double value;
};

int main()
{

    fstream file("direct.bin", ios::binary | ios::in | ios::out | ios::trunc);

    Record data[5] = {
        {1, "Alpha", 1.1},
        {2, "Beta", 2.2},
        {3, "Gamma", 3.3},
        {4, "Delta", 4.4},
        {5, "Epsilon", 5.5}};

    for (int i = 0; i < 5; i++)
        file.write((char *)&data[i], sizeof(Record));

    int index = 2;

    file.seekp(index * sizeof(Record));

    Record update = {3, "Gamma_NEW", 99.9};

    file.write((char *)&update, sizeof(Record));

    file.seekg(0);

    Record r;

    while (file.read((char *)&r, sizeof(Record)))
    {
        cout << r.id << " " << r.name << " " << r.value << endl;
    }

    file.close();

    return 0;
}