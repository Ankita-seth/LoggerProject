#include "Logger.h"


int main()
{
	//static LOGGER:: Logger* g_logger = LOGGER::LoggerFactory::CreateFileLogger();
	static LoggerClass::Logger* g_logger = LoggerClass::LoggerFactory::CreateConsoleLogger();
	LOG() << "Begin";
	LOG() << "WARNING" << "My Warning";
	LOG() << "ERROR" << "My Error";
	LOG() << "TRACE" << "My Trace";
	LOG() << "INFO" << "My Info";
	LOG() << "HRESULT error: " << " at line " << __LINE__ << " in file " << __FILE__;
	LOG() << "End";
	return 0;
}
