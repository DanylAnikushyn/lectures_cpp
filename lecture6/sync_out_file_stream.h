#pragma once 

#include <iostream>
#include <mutex>
#include <fstream>

class SyncOutFileStream
{
public:
    SyncOutFileStream(const std::string& filename);
    std::ostream& operator<<(const std::string& message);
private:
    std::ofstream m_ofstream;
    static std::mutex m_mutex;
};