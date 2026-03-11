#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int PAGE_SIZE = 4096;

int main() {
    ifstream file("data.txt");
    if (!file) {
        cout << "File not found\n";
        return 1;
    }

    vector<string> pages;
    string buffer, line;

    while (getline(file, line)) {
        buffer += line + "\n";
        if (buffer.size() >= PAGE_SIZE) {
            pages.push_back(buffer);
            buffer.clear();
        }
    }
    if (!buffer.empty())
        pages.push_back(buffer);

    cout << "Total Pages: " << pages.size() << endl;

    cout << "Reading page 0:\n";
    cout << pages[0].substr(0, 50) << "...\n";

    return 0;
}