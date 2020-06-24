#ifndef _LOG4CPLUSPLUS_IMP_H_
#define _LOG4CPLUSPLUS_IMP_H_

#include "../include/log4cplusplus.h"

#include <log4cplus/logger.h>
#include <log4cplus/initializer.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/property.h>

namespace log4cplus
{
	class Log4CPlusPlusImp final : public Log4CPlusPlus
	{
	private:
		Log4CPlusPlusImp();
		~Log4CPlusPlusImp();
		Log4CPlusPlusImp(const Log4CPlusPlusImp&) = delete;
		Log4CPlusPlusImp& operator = (const Log4CPlusPlusImp&) = delete;

	protected:
		std::wstring GetFullLogFileName(const wchar_t *file_path_base, const wchar_t *file_name);

	public:
		static Log4CPlusPlusImp* GetInstance();

	public:
		void Init(const wchar_t *file_path = L"", const wchar_t *file_name = DEFALT_LOG_FILE_NAME) override;
		void UnInit() override;
		
		void EnableDebuggerOutput(bool enable = false) override;
		void EnableConsoleOutput(bool enable = false) override;

		void WriteLog(Log4CPlusPlusLevel logLevel, const char* file, int line, const char* function, const wchar_t *format, ...) override;

	private:
		bool m_isInit;
		Logger m_logger;
		std::unique_ptr<Initializer> m_pInitializer;
	};
}

#endif	// _LOG4CPLUSPLUS_IMP_H_
