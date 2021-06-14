#include "sync_out_file_stream.h"

#include <mutex>
#include <iostream>
#include <fstream>

SyncOutFileStream::SyncOutFileStream(const std::string& filename) : m_ofstream(filename, std::ios::app)
{
    if (!m_ofstream.is_open()) 
    {
        throw std::runtime_error("unable to open file");
    }
}

std::ostream& SyncOutFileStream::operator<<(const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ofstream << message;
    return m_ofstream;
}

std::mutex SyncOutFileStream::m_mutex;