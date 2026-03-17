#include <iostream>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{

    int fd = open("shared.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    flock(fd, LOCK_EX);

    const char *text = "Writing with lock\n";

    write(fd, text, strlen(text));

    flock(fd, LOCK_UN);

    close(fd);

    cout << "Write finished\n";

    return 0;
}