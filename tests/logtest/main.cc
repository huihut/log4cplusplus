#include "log4cplusplus.h"

int main(int argc, char *argv[])
{
	log4cplus::Log4CPlusPlus* log = GetLog4CPlusPlusInstance();
	if (log)
	{
		log->Init();
		log->EnableDebuggerOutput(true);
		log->EnableConsoleOutput(true);

		LOG4CPLUSPLUS_DEBUG(L"log test");
		LOG4CPLUSPLUS_INFO(L"log test %s", L"info");
		LOG4CPLUSPLUS_WARN(L"log test %s %d", L"warn", 123);
		LOG4CPLUSPLUS_ERROR(L"log test %f", 3.14);

		log->UnInit();
	}

	return 0;
}
