///////////////////////////////////////////////////////////
//  Logger.h
//  Implementation of the Class Logger
//  Created on:      23-Nov-2024 12:34:05 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_9EC45349_B2CF_493d_81AF_37A49C6488DB__INCLUDED_)
#define EA_9EC45349_B2CF_493d_81AF_37A49C6488DB__INCLUDED_

#include <fstream>
#include <mutex>
#include <cstring>
#include <vector>

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum LogLevel
	{
		NONE = 0x0,
		DEBUG = 0x1,
		INFO = 0x2,
		WARN = 0x4,
		ERR = 0x10,
		FATAL = 0x20,
		ALL = 0xFF
	};

	class Logger
	{

	public:
		/**
		 * Destructor
		 */
		virtual ~Logger();
		/**
		 * Initialize logger
		 */
		static bool Init(const char *appName = nullptr, int levels = 0xFF, const char *fileName = nullptr);
		/**
		 * Write a line of trace log
		 */
		static void Log(const char *sourceFile, int lineNo, const char *func, T::LogLevel level, const char *format, ...);
		/**
		 * Shorten file path
		 */
		inline static std::string shorten(const char *input, unsigned char count = 3)
		{
			std::string source(input);
			std::vector<int> separators;
#ifdef _WINDOWS
			char sep[2] = {'\\', '\0'};
#else  // ! _WINDOWS
			char sep[2] = {'/', '\0'};
#endif //_WINDOWS
			int pos = source.find(sep);
			while (pos != -1)
			{
				separators.push_back(pos);
				pos = source.find(sep, pos + 1);
			}
			unsigned char temp_count = 1;
			auto idx = separators.size() - 1;
			while (idx >= 0 && temp_count < count)
			{
				temp_count++;
				idx--;
			}
			if (idx == -1)
				return source;
			else
				return source.substr(separators[idx] + 1);
		}

	private:
		/**
		 * Constructor
		 */
		explicit Logger();

	private:
		static int sEnabledLevels;
		static int sIndex;
		static std::ofstream sLogStream;
		static std::mutex sMutex;
		static std::string sAppName;
	};

#if defined(__DEBUG__) || defined(DEBUG) || defined(_DEBUG)
#define LOGD(fmt, ...) T::Logger::Log(T::Logger::shorten(__FILE__).c_str(), __LINE__, __FUNCTION__, T::LogLevel::DEBUG, fmt, ##__VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif // defined(__DEBUG__) || defined(DEBUG) || defined(_DEBUG)
#define LOGI(fmt, ...) T::Logger::Log(T::Logger::shorten(__FILE__).c_str(), __LINE__, __FUNCTION__, T::LogLevel::INFO, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) T::Logger::Log(T::Logger::shorten(__FILE__).c_str(), __LINE__, __FUNCTION__, T::LogLevel::WARN, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) T::Logger::Log(T::Logger::shorten(__FILE__).c_str(), __LINE__, __FUNCTION__, T::LogLevel::ERR, fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) T::Logger::Log(T::Logger::shorten(__FILE__).c_str(), __LINE__, __FUNCTION__, T::LogLevel::FATAL, fmt, ##__VA_ARGS__)

#define FI() LOGD("[IN]")
#define FM(fmt, ...) LOGD(fmt, ##__VA_ARGS__)
#define FO() LOGD("[OUT]")
#define FS(s) LOGD(":%s", s)

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_9EC45349_B2CF_493d_81AF_37A49C6488DB__INCLUDED_)
