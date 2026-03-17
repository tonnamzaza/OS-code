#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{

    string password;
    cout << "Enter password: ";
    cin >> password;

    bool upper = false, lower = false, digit = false;

    for (char c : password)
    {
        if (isupper(c))
            upper = true;
        if (islower(c))
            lower = true;
        if (isdigit(c))
            digit = true;
    }

    if (password.length() >= 8 && upper && lower && digit)
        cout << "Strong password\n";
    else
        cout << "Weak password\n";

    return 0;
}