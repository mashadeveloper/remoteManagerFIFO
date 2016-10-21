#ifndef FIFOPIPE_H
#define FIFOPIPE_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define NAMEDPIPEREAD_NAME "/tmp/piperead"
#define NAMEDPIPEWRITE_NAME "/tmp/pipewrite"
#define BUFSIZE 50

class Fifopipe
{
public:
    Fifopipe();
    ~Fifopipe();

    string ReadFromPipe();
    void WriteToPipe(string info);

private:
    int _fdRead;
    int _fdWrite;
};

#endif // FIFOPIPE_H
