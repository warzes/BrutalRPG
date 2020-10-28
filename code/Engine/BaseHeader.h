#pragma once

//-----------------------------------------------------------------------------
// Base Header
//-----------------------------------------------------------------------------
#include "EngineVersionConst.h"
#include "DetectCompiler.h"
#include "DetectOS.h"
#include "VersionOSConst.h"
#include "ConfigEngine.h"
#include "BaseMacros.h"
#include "InlineFunc.h"

//-----------------------------------------------------------------------------
// Header config
//-----------------------------------------------------------------------------
#define _STL_WARNING_LEVEL 3

#if SE_PLATFORM_WINDOWS
#	include "Win32PlatformDefinitions.h"
#endif // SE_PLATFORM_WINDOWS

//-----------------------------------------------------------------------------
// Disable warning
//-----------------------------------------------------------------------------
SE_PRAGMA_WARNING_DISABLE_MSVC(4514); // unreferenced inline function has been removed;
SE_PRAGMA_WARNING_DISABLE_MSVC(4625);
SE_PRAGMA_WARNING_DISABLE_MSVC(4626);
SE_PRAGMA_WARNING_DISABLE_MSVC(4820);
SE_PRAGMA_WARNING_DISABLE_MSVC(5026);
SE_PRAGMA_WARNING_DISABLE_MSVC(5027);

//-----------------------------------------------------------------------------
// STD C++17 Header
//-----------------------------------------------------------------------------
SE_PRAGMA_WARNING_LEVEL(0)
SE_PRAGMA_WARNING_DISABLE_MSVC(4355); // 
SE_PRAGMA_WARNING_DISABLE_MSVC(5204); // 

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <stdexcept>

#include <algorithm>
#include <chrono>
#include <optional>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>

#include <queue>
#include <vector>
#include <array>
#include <set>
#include <stack>
#include <unordered_map>

#include <atomic>
#include <mutex>
#include <thread>
#include <future>

SE_PRAGMA_WARNING_POP

//-----------------------------------------------------------------------------
// 3rd-party Header
//-----------------------------------------------------------------------------
SE_PRAGMA_WARNING_LEVEL(0)

#if SE_DIRECT3D11
#endif

#if SE_DIRECT3D12
#endif

#if SE_OPENGLES
#endif

#if SE_OPENGL
#endif

#if SE_VULKAN
#endif

SE_PRAGMA_WARNING_POP

//-----------------------------------------------------------------------------
// Platform Header
//-----------------------------------------------------------------------------
SE_PRAGMA_WARNING_LEVEL(0);
#if SE_PLATFORM_WINDOWS
#	include <Windows.h>
#	include <VersionHelpers.h>
#	include <wrl.h> // Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#	include <shellapi.h>
#	include <strsafe.h>
#	undef near
#	undef far
#else
#	include <sys/time.h>
#endif // SE_PLATFORM_*
SE_PRAGMA_WARNING_POP