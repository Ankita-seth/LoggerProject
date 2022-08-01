#pragma once
#include<iostream>
#include <fstream>

using namespace std;
namespace LoggerClass
{
	class Logger                                                                                      //Abstract class 
	{
	public:
		virtual ostream& GetStream() = 0;                                                         //Pure Virtual Function
	};

	class ConsoleLogger :public Logger
	{
		ostream& GetStream();
	};

	class FileLogger :public Logger
	{
	private:
		ofstream m_filelogger;                                                                    //File create for write
		public:
			//FILE* pFile = fopen("ankita.log", "a");
			//std::ostream os;
			FileLogger(std::string filename)                                                  //Constructor
			{
				m_filelogger.open(filename.c_str(), ios_base::out);                       //File opened
			};

			~FileLogger()                                                                     //Destructor
			{
				m_filelogger.close();                                                     //File closed
			};

   		    ostream& GetStream();
	};

	class LoggerFactory
	{
	public:
		static Logger* CreateFileLogger(std::string FilePath);
		static Logger* CreateConsoleLogger();
	};

	static LoggerClass::Logger* g_logger = LoggerClass::LoggerFactory::CreateFileLogger("ankita.log");                 //Object Creation of logger class
	//static Logger* g_logger = LoggerFactory::CreateConsoleLogger();
    #define LOG() g_logger->GetStream()                                                                     //Macro defined
}
