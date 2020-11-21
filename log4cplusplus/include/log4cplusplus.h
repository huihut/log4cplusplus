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
#define LOG4CPLUSPLUS_DEBUG(pLog4CPlusPlus, ...)\
{\
	if(pLog4CPlusPlus)\
	{\
		pLog4CPlusPlus->WriteLog(log4cplus::LogDebugLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
	}\
}

// 普通日志
#define LOG4CPLUSPLUS_INFO(pLog4CPlusPlus, ...)\
{\
	if(pLog4CPlusPlus)\
	{\
		pLog4CPlusPlus->WriteLog(log4cplus::LogInfoLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
	}\
}

// 警告日志
#define LOG4CPLUSPLUS_WARN(pLog4CPlusPlus, ...)\
{\
	if(pLog4CPlusPlus)\
	{\
		pLog4CPlusPlus->WriteLog(log4cplus::LogWarnLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
	}\
}

// 错误日志
#define LOG4CPLUSPLUS_ERROR(pLog4CPlusPlus, ...)\
{\
	if(pLog4CPlusPlus)\
	{\
		pLog4CPlusPlus->WriteLog(log4cplus::LogErrorLevel, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);\
	}\
}

#define DEFALT_LOG_FILE_PATH L""                // 默认日志文件路径
#define DEFALT_LOG_FILE_NAME L"log.log"         // 默认日志文件名
#define DEFALT_MAX_FILE_SIZE 10 * 1024 * 1024   // 默认最大文件大小
#define DEFALT_MAX_FILE_COUNT 100			    // 默认最大文件备份数量
#define DEFALT_IS_ASYNC	true                    // 默认异步
#define DEFALT_MAX_DAYS_COUNT 15                // 默认最多保留日志天数

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
		Log4CPlusPlus() {}
		virtual ~Log4CPlusPlus() {}

	public:
		/*
			释放日志资源
		*/
		virtual void Release() = 0;

		/*
			添加文件附加器
			* file_path 日志基础文件路径，如传入 D:\\code，最终生成 D:\\code\\log\\2020-6-4\\
			* file_name 日志文件名，如 log.log
			* max_file_size 最大文件大小
			* max_file_count 最大文件数
			* is_async 是否异步
		*/
		virtual void AddFileAppender(
			const wchar_t *file_path = DEFALT_LOG_FILE_PATH,
			const wchar_t *file_name = DEFALT_LOG_FILE_NAME,
			unsigned long max_file_size = DEFALT_MAX_FILE_SIZE,
			unsigned long max_file_count = DEFALT_MAX_FILE_COUNT,
			bool is_async = DEFALT_IS_ASYNC
		) = 0;

		/*
			启用调试器附加器，如 VS调试窗口
		*/
		virtual void EnableDebuggerAppender(bool enable) = 0;

		/*
			启用控制台附加器，如 cmd
		*/
		virtual void EnableConsoleAppender(bool enable) = 0;

		/*
			获取日志的路径
		*/
		virtual const wchar_t * GetLogPath() = 0;

		/*
			打印日志，支持格式化字符串
			* logLevel 日志等级
			* file 打印日志代码所在的文件
			* line 打印日志代码所在的行
			* function 打印日志代码所在的类及方法
			* format, ... 格式化字符串，如 L"Hello %s %d", L"World", 123
		*/
		virtual void WriteLog(
			Log4CPlusPlusLevel logLevel,
			const char* file,
			int line,
			const char* function,
			const wchar_t *format, ...) = 0;

	};
}

extern "C" LOG4CPLUSPLUS_API log4cplus::Log4CPlusPlus* __cdecl CreateLog4CPlusPlus();

#endif	// _LOG4CPLUSPLUS_H_