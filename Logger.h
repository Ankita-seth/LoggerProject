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

		ostream& GetStream();

	};

	class LoggerFactory
	{
		static Logger* CreateFileLogger(std::string FilePath);
		static Logger* CreateConsoleLogger();

	
	};

	
}