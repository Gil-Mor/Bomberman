#include "LevelFileException.h"


LevelFileException::LevelFileException(const string& message)
    : std::runtime_error(message)
{
}


