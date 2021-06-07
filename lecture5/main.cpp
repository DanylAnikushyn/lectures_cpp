#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstring>

class Logger 
{
public:
    virtual ~Logger() {}; 
    virtual void log(const std::string& message) const = 0;
};

class ConsoleLogger : public Logger 
{
public:
    void log(const std::string& message) const override
    {
        auto current = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        char *t = ctime(&current_time);
        if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
        std::cout << level << ", " << t << ": [" << message << "]" << std::endl;
        ++level;
    }
private:
    static unsigned level;
};

unsigned ConsoleLogger::level = 0;

class FileLogger : public Logger
{
public:
    void log(const std::string& message) const override
    {
        std::ofstream out;
        out.open("logs.txt", std::ofstream::out | std::ofstream::app);
        auto current = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        char *t = ctime(&current_time);
        if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
        out << level << ", " << t << ": [" << message << "]" << std::endl;
        ++level;
        out.close();
    }
private:
    static unsigned level;
};

unsigned FileLogger::level = 0;

class OutputStream
{
public:
    virtual ~OutputStream() {};
    virtual Logger* getLogger() const = 0;
    void log(const std::string& message) const 
    {
        Logger* logger = this->getLogger();
        logger->log(message);
        delete logger;
    }
};

class ConsoleOutputStream : public OutputStream
{
public: 
    Logger* getLogger() const override
    {
        return new ConsoleLogger();
    }
};

class FileOutputStream : public OutputStream
{
public:
    Logger* getLogger() const override
    {
        return new FileLogger();
    }
};

int main(int argc, char* argv[])
{
    OutputStream* output = new FileOutputStream();
    output->log("hello");
    output->log("world");
    return 0;
}