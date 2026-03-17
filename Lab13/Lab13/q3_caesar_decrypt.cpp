#include <iostream>
#include <string>
using namespace std;

int main()
{

    string text;
    int key;

    cout << "Enter encrypted text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    for (char &c : text)
    {

        if (isalpha(c))
        {

            char base = isupper(c) ? 'A' : 'a';

            c = (c - base - key + 26) % 26 + base;
        }
    }

    cout << "Decrypted: " << text << endl;

    return 0;
}