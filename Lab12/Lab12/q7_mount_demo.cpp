#include <iostream>
#include <sys/mount.h>
#include <cstring>
#include <cerrno>

using namespace std;

int main()
{

    const char *source = "/dev/sdb1";
    const char *target = "/mnt/usb";
    const char *type = "vfat";

    if (mount(source, target, type, MS_RDONLY, "") == -1)
    {
        cout << "Mount failed: " << strerror(errno) << endl;
        return 1;
    }

    cout << "Mount success\n";

    return 0;
}