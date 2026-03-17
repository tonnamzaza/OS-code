#include <iostream>
#include <string>
using namespace std;

int main()
{

    string text;

    cout << "Enter text: ";
    getline(cin, text);

    int hash = 0;

    for (char c : text)
    {
        hash += c;
    }

    cout << "Hash value: " << hash << endl;

    return 0;
}