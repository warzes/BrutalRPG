#pragma once

#if !SE_PLATFORM_EMSCRIPTEN

#include "LogVerbosity.h"

class CoreLogThread
{
public:
	void LogLoop();

protected:
	CoreLogThread();
	~CoreLogThread();

	void close();
	void print(const std::string& str, const LogVerbosity verbosity = LogVerbosity::Info) const;

	struct logEntry
	{
		logEntry(const LogVerbosity initVerbosity, const std::string& initString) noexcept
			: verbosity(initVerbosity)
			, str(initString)
		{
		}

		LogVerbosity verbosity;
		std::string  str;
	};

	mutable std::condition_variable m_queueCondition;
	mutable std::mutex m_queueMutex;
	mutable std::queue<logEntry> m_logQueue;
	std::thread m_thread;

	bool m_isClose = false;
	bool m_quitCommand = false;
};

#endif // !SE_PLATFORM_EMSCRIPTEN