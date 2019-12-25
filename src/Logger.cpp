#include "Logger.h"

Logger::Logger()
{
    file.open("../log.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
}

Logger::~Logger()
{
    file.close();
}

void Logger::log(const string& m)
{
    _errors++;
    file << std::to_string(_errors) + ". " + m + "\n\n";
}

Logger& Logger::getInstance()
{
    static Logger _instance;
    return _instance;
}
