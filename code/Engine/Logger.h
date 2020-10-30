#pragma once

#include "CoreLogSystem.h"

#define SE_LOG(level, str)  {CoreLogSystem::Print(str, level);}
#define SE_LOG_ERROR(str)   {CoreLogSystem::Print(str, LogVerbosity::Error);}
#define SE_LOG_WARNING(str) {CoreLogSystem::Print(str, LogVerbosity::Warning);}
#define SE_LOG_INFO(str)    {CoreLogSystem::Print(str, LogVerbosity::Info);}



// TEMP
inline void fatal(bool cond, const char* msg)
{
	if (!cond) {
		SE_LOG_ERROR(msg);
		abort();
	}
}

#define SE_FATAL(cond) fatal((cond), #cond);
