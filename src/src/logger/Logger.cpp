///////////////////////////////////////////////////////////
//  Logger.cpp
//  Implementation of the Class Logger
//  Created on:      23-Nov-2024 12:34:05 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Logger.hpp"
#include <exception>
#include <stdarg.h>
#include <iostream>
#include <ctime>

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int Logger::sEnabledLevels = 0xFF;
	std::ofstream Logger::sLogStream;
	std::mutex Logger::sMutex;
	std::string Logger::sAppName;
	int Logger::sIndex = 0;

	/**
	 * Constructor
	 */
	Logger::Logger()
	{
	}

	/**
	 * Destructor
	 */
	Logger::~Logger()
	{
		if (sLogStream.is_open())
			sLogStream.close();
	}

	/**
	 * Initialize logger
	 */
	bool Logger::Init(const char *appName, int levels, const char *fileName)
	{
		if (appName != nullptr)
			sAppName = appName;
		sEnabledLevels = levels;
		sIndex = 1;
		if (fileName != nullptr)
		{
			if (sLogStream.is_open())
				sLogStream.close();
			try
			{
				sLogStream.open(fileName, std::ios_base::out);
			}
			catch (...)
			{
				sLogStream.close();
				return false;
			}
		}
		return true;
	}

	/**
	 * Write a line of trace log
	 */
	void Logger::Log(const char *sourceFile, int lineNo, const char *func, LogLevel level, const char *format, ...)
	{
		if ((level & sEnabledLevels) == 0)
		{
			return;
		}

		std::lock_guard<std::mutex> locker(sMutex);
		char log[256] = {0};
		va_list vl;
		va_start(vl, format);
		vsnprintf(log, 255, format, vl);
		va_end(vl);
		char date_time[65] = {0};
		std::time_t now = std::time(nullptr);
		struct tm *local_time = nullptr;
#ifdef _WINDOWS
		struct tm local = {0};
		local_time = &local;
		localtime_s(&local, &now);
#else  // ! _WINDOWS
		local_time = std::localtime(&now);
#endif //_WINDOWS
		snprintf(date_time, 64, "%.4d/%.2d/%.2d - %.2d:%.2d:%.2d", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

		switch (level)
		{
		case LogLevel::DEBUG:
			if (sLogStream.is_open())
				sLogStream << sIndex << " " << date_time << "[" << sAppName.c_str() << "][D]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			else
				std::cout << sIndex << " " << date_time << "[" << sAppName.c_str() << "][D]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			break;
		case LogLevel::INFO:
			if (sLogStream.is_open())
				sLogStream << sIndex << " " << date_time << "[" << sAppName.c_str() << "][I]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			else
				std::cout << sIndex << " " << date_time << "[" << sAppName.c_str() << "][I]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			break;
		case LogLevel::WARN:
			if (sLogStream.is_open())
				sLogStream << sIndex << " " << date_time << "[" << sAppName.c_str() << "][W]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			else
				std::cout << sIndex << " " << date_time << "[" << sAppName.c_str() << "][W]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			break;
		case LogLevel::ERR:
			if (sLogStream.is_open())
				sLogStream << sIndex << " " << date_time << "[" << sAppName.c_str() << "][E]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			else
				std::cout << sIndex << " " << date_time << "[" << sAppName.c_str() << "][E]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			break;
		case LogLevel::FATAL:
			if (sLogStream.is_open())
				sLogStream << sIndex << " " << date_time << "[" << sAppName.c_str() << "][F]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			else
				std::cout << sIndex << " " << date_time << "[" << sAppName.c_str() << "][F]" << sourceFile << "[" << lineNo << "]" << "<<" << func << ">>" << log << std::endl;
			break;
		default:
			break;
		}

		sIndex++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
}