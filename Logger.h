#pragma once
#include<iostream>
#include <fstream>



using namespace std;
namespace LoggerClass
{

	class Logger
	{
	public:
		virtual ostream& GetStream() = 0;
	};

	class ConsoleLogger :public Logger
	{
		ostream& GetStream();
	};

	class FileLogger :public Logger
	{
	private:
		ofstream m_filelogger;

		public:
			//FILE* pFile = fopen("ankita.log", "a");
			//std::ostream os;

			FileLogger(std::string filename)
			{
				m_filelogger.open(filename.c_str(), ios_base::out);
			};

			~FileLogger()
			{
				m_filelogger.close();
			};

   		    ostream& GetStream();
	};

	class LoggerFactory
	{
	public:
		static Logger* CreateFileLogger(std::string FilePath);
		static Logger* CreateConsoleLogger();
	};

	static LoggerClass::Logger* g_logger = LoggerClass::LoggerFactory::CreateFileLogger("ankita.log");
	//static Logger* g_logger = LoggerFactory::CreateConsoleLogger();
    #define LOG() g_logger->GetStream()
}