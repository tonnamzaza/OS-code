#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{

    srand(time(0));

    const string chars =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int length = 10;

    for (int i = 0; i < length; i++)
    {

        cout << chars[rand() % chars.length()];
    }

    cout << endl;

    return 0;
}