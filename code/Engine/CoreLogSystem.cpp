#include "stdafx.h"
#include "CoreLogSystem.h"
#include "PlatformCoreLog.h"
#include "AssertMacros.h"
//-----------------------------------------------------------------------------
CoreLogSystem::CoreLogSystem(const CoreLogSettings& settings)
{
	m_instance = this;
	m_instance->m_settings = settings;
}
//-----------------------------------------------------------------------------
void CoreLogSystem::Print(std::string_view str, const LogVerbosity verbosity)
{
#if SE_PLATFORM_EMSCRIPTEN
	PlatformLogPrint(str, verbosity);
#else
	SE_ASSERT(m_instance, "CoreLogSystem no create!!!");
	m_instance->print(str.data(), verbosity);
#endif
}
//-----------------------------------------------------------------------------