#pragma once

#include "CoreLogSettings.h"
#if !SE_PLATFORM_EMSCRIPTEN
#	include "CoreLogThread.h"
#else
#	include "LogVerbosity.h"
#endif

class CoreLogSystem
#if !SE_PLATFORM_EMSCRIPTEN
	: public CoreLogThread
#endif
{
public:
	CoreLogSystem(const CoreLogSettings &settings);

	static void Print(std::string_view str, const LogVerbosity verbosity = LogVerbosity::Info);

private:
	CoreLogSystem(const CoreLogSystem&) = delete;
	CoreLogSystem operator=(const CoreLogSystem&) = delete;

	static inline CoreLogSystem* m_instance = nullptr;
	CoreLogSettings m_settings;
};