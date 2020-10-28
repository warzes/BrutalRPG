#pragma once

#include "LogVerbosity.h"
#if SE_PLATFORM_WINDOWS
#	include "WindowsPlatformCoreLog.h"
#else
#	error "non"
#endif