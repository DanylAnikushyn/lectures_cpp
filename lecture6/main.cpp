#include <iostream>

#include "sync_out_file_stream.h"

void WriteToFile(const std::string& message) 
{
    // all code that can be screwed up is encapsulated inside 
    // SyncOutFileStream class and we can use it as output stream
    SyncOutFileStream file("example.txt");
    file << message << std::endl;
}

int main(int argc, char* argv[])
{
    WriteToFile("hello");
    return 0;
}