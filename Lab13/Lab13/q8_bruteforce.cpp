#include <iostream>
#include <string>
using namespace std;

int main()
{

    string target = "123";

    for (int i = 0; i <= 999; i++)
    {

        string guess = to_string(i);

        if (guess == target)
        {
            cout << "Password found: " << guess << endl;
            break;
        }
    }

    return 0;
}