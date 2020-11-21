#include "log4cplusplus.h"

int main(int argc, char *argv[])
{
	log4cplus::Log4CPlusPlus* log = CreateLog4CPlusPlus();
	if (log)
	{
		log->AddFileAppender();
		log->EnableDebuggerAppender(true);
		log->EnableConsoleAppender(true);

		LOG4CPLUSPLUS_DEBUG(log, L"log test");
		LOG4CPLUSPLUS_INFO(log, L"log test %s", L"info");
		LOG4CPLUSPLUS_WARN(log, L"log test %s %d", L"warn", 123);
		LOG4CPLUSPLUS_ERROR(log, L"log test %f", 3.14);
		LOG4CPLUSPLUS_ERROR(log, L"中文日志测试!!");

		log->Release();
	}
	return 0;
}