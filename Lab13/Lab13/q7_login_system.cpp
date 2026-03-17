#include <iostream>
using namespace std;

int main()
{

    string user, pass;

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234")
        cout << "Login success\n";
    else
        cout << "Access denied\n";

    return 0;
}