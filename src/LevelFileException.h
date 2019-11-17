#pragma once
/* 
Exception that is thrown when an error occurred while reading level file. 
*/
#include <stdexcept>
#include <string>
using std::string;

class LevelFileException : public std::runtime_error
{
public:
    LevelFileException(const string& message);
};

