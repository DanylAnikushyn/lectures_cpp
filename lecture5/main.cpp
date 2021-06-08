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
    void log(const std::string& message) const
    {
        auto current = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        char *time = ctime(&current_time);
        if (time[strlen(time)-1] == '\n') time[strlen(time)-1] = '\0';
        write(message, time);
    }
protected:
    virtual void write(const std::string& message, const std::string& time) const = 0;
};

class ConsoleLogger : public Logger 
{
protected:
    void write(const std::string& message, const std::string& time) const override
    {
        std::cout << level << ", " << time << ": [" << message << "]" << std::endl;
        ++level;
    }
private:
    static unsigned level;
};

unsigned ConsoleLogger::level = 0;

class FileLogger : public Logger
{
protected:
    void write(const std::string& message, const std::string& time) const override
    {
        std::ofstream out;
        out.open("logs.txt", std::ofstream::out | std::ofstream::app);
        out << level << ", " << time << ": [" << message << "]" << std::endl;
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
    auto file_output = std::make_unique<FileOutputStream>();
    file_output->log("hello");
    auto console_output = std::make_unique<ConsoleOutputStream>();
    console_output->log("something happened 1");
    file_output->log("world");
    console_output->log("something happened 2");
    console_output->log("something happened 3");
    return 0;
}