#ifndef _LOG4CPLUSPLUS_H_
#define _LOG4CPLUSPLUS_H_

#ifdef WIN32
#if defined(LOG4CPLUSPLUS_EXPORT)
#define LOG4CPLUSPLUS_API __declspec(dllexport)
#else
#define LOG4CPLUSPLUS_API __declspec(dllimport)
#endif
#else
#define LOG4CPLUSPLUS_API __attribute__((visibility("default")))
#endif

// 调试日志
#define LOG4CPLUSPLUS_DEBUG(...)\
{\
	GetLog4CPlusPlusInstance()->WriteLog(log4cplus::LogDebugLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
}

// 普通日志
#define LOG4CPLUSPLUS_INFO(...)\
{\
	GetLog4CPlusPlusInstance()->WriteLog(log4cplus::LogInfoLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
}

// 警告日志
#define LOG4CPLUSPLUS_WARN(...)\
{\
	GetLog4CPlusPlusInstance()->WriteLog(log4cplus::LogWarnLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
}

// 错误日志
#define LOG4CPLUSPLUS_ERROR(...)\
{\
	GetLog4CPlusPlusInstance()->WriteLog(log4cplus::LogErrorLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
}

#define DEFALT_LOG_FILE_NAME L"log.log"

namespace log4cplus
{
	enum Log4CPlusPlusLevel
	{
		LogDebugLevel = 10000,
		LogInfoLevel = 20000,
		LogWarnLevel = 30000,
		LogErrorLevel = 40000
	};

	class Log4CPlusPlus
	{
	public:
		virtual ~Log4CPlusPlus() {}

	public:
		/*
			初始化日志
			* file_path 日志基础文件路径，如传入 D:\\code，最终生成 D:\\code\\log\\2020-6-4\\
			* file_name 日志文件名，如 log.log
		*/
		virtual void Init(const wchar_t *file_path = L"", const wchar_t *file_name = DEFALT_LOG_FILE_NAME) = 0;
		
		/*
			反初始化日志
		*/
		virtual void UnInit() = 0;

		/*
			日志同时输出到调试器，如 VS调试窗口
		*/
		virtual void EnableDebuggerOutput(bool enable) = 0;

		/*
			日志同时输出到控制台，如 cmd
		*/
		virtual void EnableConsoleOutput(bool enable) = 0;

		/*
			打印日志，支持格式化字符串
			* logLevel 日志等级
			* file 打印日志代码所在的文件
			* line 打印日志代码所在的行
			* function 打印日志代码所在的类及方法
			* format, ... 格式化字符串，如 L"Hello %s %d", L"World", 123
		*/
		virtual void WriteLog(Log4CPlusPlusLevel logLevel, const char* file, int line, const char* function, const wchar_t *format, ...) = 0;

	protected:
		Log4CPlusPlus() {}

	private:
		Log4CPlusPlus(const Log4CPlusPlus&) = delete;
		Log4CPlusPlus& operator = (const Log4CPlusPlus&) = delete;

	};
}

extern "C" LOG4CPLUSPLUS_API log4cplus::Log4CPlusPlus* __cdecl GetLog4CPlusPlusInstance();

#endif	// _LOG4CPLUSPLUS_H_
