#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <memory>

class Logger 
{
public:
    virtual ~Logger() {}; 
    void log(const std::string& message)
    {
        auto current = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        char *buffer = new char[26];
        ctime_r(&current_time, buffer);
        if (buffer[strlen(buffer)-1] == '\n') buffer[strlen(buffer)-1] = '\0';
        write(message, buffer);
        delete[] buffer;
    }
protected:
    virtual void write(const std::string& message, const std::string& time) = 0;
};

class ConsoleLogger : public Logger 
{
public:
    ConsoleLogger()
    {
        level = 0;
    }
protected:
    void write(const std::string& message, const std::string& time) override
    {
        std::cout << level << ", " << time << ": [" << message << "]" << std::endl;
        ++level;
    }
private:
    unsigned level;
};

class FileLogger : public Logger
{
public:
    FileLogger()
    {
        level = 0;
        out.open("logs.txt", std::ofstream::out | std::ofstream::app);
    }
protected:
    void write(const std::string& message, const std::string& time) override
    {
        out << level << ", " << time << ": [" << message << "]" << std::endl;
        ++level;
    }
private:
    unsigned level;
    std::ofstream out;
};

class OutputStream
{
public:
    virtual ~OutputStream() {};
    virtual std::unique_ptr<Logger> getLogger() const = 0;
};

class ConsoleOutputStream : public OutputStream
{
public: 
    std::unique_ptr<Logger> getLogger() const override
    {
        return std::make_unique<ConsoleLogger>();
    }
};

class FileOutputStream : public OutputStream
{
public:
    std::unique_ptr<Logger> getLogger() const override
    {
        return std::make_unique<FileLogger>();
    }
};

int main(int argc, char* argv[])
{
    auto file_output = std::make_unique<FileOutputStream>();
    auto file_logger = file_output->getLogger();
    file_logger->log("hello");
    auto console_output = std::make_unique<ConsoleOutputStream>();
    auto console_logger = console_output->getLogger();
    console_logger->log("something happened 1");
    file_logger->log("world");
    console_logger->log("something happened 2");
    console_logger->log("something happened 3");
    return 0;
}