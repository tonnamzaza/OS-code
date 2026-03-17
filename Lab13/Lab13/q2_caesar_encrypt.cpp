#include <iostream>
#include <string>
using namespace std;

int main()
{

    string text;
    int key;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    for (char &c : text)
    {

        if (isalpha(c))
        {

            char base = isupper(c) ? 'A' : 'a';

            c = (c - base + key) % 26 + base;
        }
    }

    cout << "Encrypted: " << text << endl;

    return 0;
}