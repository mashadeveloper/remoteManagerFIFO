#include "fifopipe.h"

Fifopipe::Fifopipe()
{
    if ( mkfifo(NAMEDPIPEREAD_NAME, 0777) )
    {
        perror("mkfifo");
    }
    if (mkfifo(NAMEDPIPEWRITE_NAME, 0777))
    {
        perror("mkfifo");
    }

    if ( (_fdRead = open(NAMEDPIPEREAD_NAME, O_RDONLY)) <= 0 )
    {
        perror("open");
    }

    if ((_fdWrite = open(NAMEDPIPEWRITE_NAME, O_WRONLY)) <= 0)
    {
        perror("open");
    }

}

Fifopipe::~Fifopipe()
{
    close(_fdRead);
    close(_fdWrite);
    remove(NAMEDPIPEREAD_NAME);
    remove(NAMEDPIPEWRITE_NAME);
}

string Fifopipe::ReadFromPipe()
{
    int len;
    char buf[BUFSIZE];
    string str;
    do
    {
        if ( (len = read(_fdRead, buf, BUFSIZE-1)) <= 0 )
        {
            return buf;
        }
        str.append(buf, BUFSIZE);
    }while(1);
}

void Fifopipe::WriteToPipe(string info)
{
    int len;
    char buf[BUFSIZE];
    strncpy(buf, info.c_str(), sizeof(info));
    if ((len = write(_fdWrite, buf, sizeof(info))) <= 0)
    {
        perror("write");
    }
}
