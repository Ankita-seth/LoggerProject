#include "Logger.h"

LoggerClass::Logger* LoggerClass::LoggerFactory::CreateFileLogger(string FilePath)
{
    
    return new FileLogger(FilePath);
}

LoggerClass::Logger* LoggerClass::LoggerFactory::CreateConsoleLogger()
{
    return new ConsoleLogger();
}

ostream& LoggerClass::ConsoleLogger::GetStream()
{

    return std::cout;
}

ostream& LoggerClass::FileLogger::GetStream()
{
    return m_filelogger;
}


