#ifndef _LOG4CPLUSPLUS_IMP_H_
#define _LOG4CPLUSPLUS_IMP_H_

#include "../include/log4cplusplus.h"

#include <set>
#include <log4cplus/logger.h>
#include <log4cplus/initializer.h>
#include <log4cplus/hierarchy.h>

namespace log4cplus
{
	class Log4CPlusPlusImp final : public Log4CPlusPlus
	{
	public:
		Log4CPlusPlusImp();
		~Log4CPlusPlusImp();

	public:
		void Release() override;

		void AddFileAppender(
			const wchar_t *file_path = DEFALT_LOG_FILE_PATH,
			const wchar_t *file_name = DEFALT_LOG_FILE_NAME,
			unsigned long max_file_size = DEFALT_MAX_FILE_SIZE,
			unsigned long max_file_count = DEFALT_MAX_FILE_COUNT,
			bool is_async = DEFALT_IS_ASYNC
		) override;

		void EnableDebuggerAppender(bool enable = false) override;
		void EnableConsoleAppender(bool enable = false) override;

		const wchar_t * GetLogPath() override;

		void WriteLog(
			Log4CPlusPlusLevel logLevel,
			const char* file,
			int line,
			const char* function,
			const wchar_t *format, ...) override;

	private:
		std::wstring GetFullLogFileName(const wchar_t *file_path_base, const wchar_t *file_name);
		bool FileAppenderPathExist(const std::wstring& path);
		bool AddFileAppenderPath(const std::wstring& path);

	private:
		Logger m_logger;
		std::unique_ptr<Initializer> m_pInitializer;
		std::unique_ptr<Hierarchy> m_pHierarchy;
		std::set<std::wstring> m_fileAppenderPath;
		std::wstring m_log_path;
	};
}

#endif	// _LOG4CPLUSPLUS_IMP_H_