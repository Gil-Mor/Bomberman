#pragma once
/* 
Singleton that logs error to a log file. 
*/
#include <string>
#include <fstream>

using std::ofstream;
using std::string;

class Logger
{
public:
    static Logger& getInstance();

    void log(const string& message);

    ~Logger();

private:

    ofstream file;

    // error counter.
    size_t _errors = 0;


    // make ctors and assignment operator private.
    Logger();
    Logger(const Logger&);
    Logger& operator=(Logger const& copy);
};

