#include "log4cplusplusimp.h"

#include <iostream>
#include <ctime>

#include <log4cplus/layout.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/win32debugappender.h>
#include <log4cplus/win32consoleappender.h>

#define DEBUGGER_APPENDER_NAME LOG4CPLUS_TEXT("debuggerAppender")
#define CONSOLE_APPENDER_NAME LOG4CPLUS_TEXT("consoleAppender")
#define FILE_APPENDER_NAME LOG4CPLUS_TEXT("fileAppender")

namespace log4cplus
{
	Log4CPlusPlusImp::Log4CPlusPlusImp()
		:m_isInit(false)
	{
	}

	void Log4CPlusPlusImp::Init(const wchar_t *file_path, const wchar_t *file_name)
	{
		if (m_isInit)
			return;

		std::locale::global(std::locale("chs"));

		m_pInitializer = std::make_unique<log4cplus::Initializer>();
		m_logger = Logger::getInstance(LOG4CPLUS_TEXT("main"));

		{
			// 主日志文件
			std::wstring& main_filename = GetFullLogFileName(file_path, file_name);
			log4cplus::SharedFileAppenderPtr mainAppender(
				new RollingFileAppender(
					main_filename.c_str(),
					10 * 1024 * 1024, 
					9999, 
					true, 
					true));
			mainAppender->setName(FILE_APPENDER_NAME);
			mainAppender->getloc();
			mainAppender->setLayout(std::unique_ptr<Layout>(
				new PatternLayout(LOG4CPLUS_TEXT("[%D{%Y-%m-%d %H:%M:%S.%q}] [%t] %-5p (%F:%L::%M) %m%n"))));
			m_logger.addAppender(SharedAppenderPtr(mainAppender.get()));
		}

		m_isInit = true;
	}

	void Log4CPlusPlusImp::UnInit()
	{
		m_logger.shutdown();
		m_pInitializer.reset();
		m_isInit = false;
	}

	Log4CPlusPlusImp::~Log4CPlusPlusImp()
	{
	}

	Log4CPlusPlusImp* Log4CPlusPlusImp::GetInstance()
	{
		static Log4CPlusPlusImp instance;
		return &instance;
	}

	// 获取完全的日志路径名
	std::wstring Log4CPlusPlusImp::GetFullLogFileName(const wchar_t *file_path_base, const wchar_t *file_name)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);
		std::wstring data = std::to_wstring(1900 + ltm->tm_year) + L"-" + std::to_wstring(1 + ltm->tm_mon) + L"-" + std::to_wstring(ltm->tm_mday);

		std::wstring s_file_path_base(file_path_base);
		std::wstring s_file_name(file_name);
		if (s_file_path_base.size() == 0)
		{
			return L"./log/" + data + L"/" + s_file_name;
		}

		std::wstring filename;
		auto& end_char = s_file_path_base.back();
		if (end_char == L'/' || end_char == L'\\')
		{
			filename = s_file_path_base + L"log/" + data + L"/" + s_file_name;
		}
		else
		{
			filename = s_file_path_base + L"/log/" + data + L"/" + s_file_name;
		}
		return filename;
	}

	// 调试日志
	void Log4CPlusPlusImp::EnableDebuggerOutput(bool enable)
	{
		SharedAppenderPtr debuggerAppender = m_logger.getAppender(DEBUGGER_APPENDER_NAME);

		// 若需启用，且没有添加，则添加
		if (enable && !debuggerAppender)
		{
			debuggerAppender = new Win32DebugAppender();
			debuggerAppender->setName(DEBUGGER_APPENDER_NAME);
			debuggerAppender->setLayout(std::unique_ptr<Layout>(
				new PatternLayout(LOG4CPLUS_TEXT("[%D{%Y-%m-%d %H:%M:%S.%q}] [%t] %-5p (%F:%L::%M) %m%n"))));
			m_logger.addAppender(SharedAppenderPtr(debuggerAppender.get()));
		}
		// 若需禁用，且已经添加，则移除
		else if(!enable && debuggerAppender)
		{
			m_logger.removeAppender(DEBUGGER_APPENDER_NAME);
		}
	}

	// 控制台日志
	void Log4CPlusPlusImp::EnableConsoleOutput(bool enable)
	{
		SharedAppenderPtr consoleAppender = m_logger.getAppender(CONSOLE_APPENDER_NAME);

		// 若需启用，且没有添加，则添加
		if (enable && !consoleAppender)
		{
			consoleAppender = new Win32ConsoleAppender();
			consoleAppender->setName(CONSOLE_APPENDER_NAME);
			consoleAppender->setLayout(std::unique_ptr<Layout>(
				new PatternLayout(LOG4CPLUS_TEXT("[%D{%Y-%m-%d %H:%M:%S.%q}] [%t] %-5p (%F:%L::%M) %m%n"))));
			m_logger.addAppender(SharedAppenderPtr(consoleAppender.get()));
		}
		// 若需禁用，且已经添加，则移除
		else if (!enable && consoleAppender)
		{
			m_logger.removeAppender(CONSOLE_APPENDER_NAME);
		}
	}

	// 打印日志
	void Log4CPlusPlusImp::WriteLog(Log4CPlusPlusLevel logLevel, const char* file, int line, const char* function, const wchar_t *format, ...)
	{
		if (!m_isInit)
			return;

		assert(format);
		LOG4CPLUS_MACRO_INSTANTIATE_SNPRINTF_BUF(var);

		tchar const * msg = nullptr;
		int ret = 0;
		std::va_list args;

		do
		{
			va_start(args, format);
			ret = var.print_va_list(msg, format, args);
			va_end(args);
		} while (ret == -1);

		if (msg)
		{
			m_logger.forcedLog(logLevel, msg, file, line, function);
		}
	}
}

log4cplus::Log4CPlusPlus* GetLog4CPlusPlusInstance()
{
	return log4cplus::Log4CPlusPlusImp::GetInstance();
}
