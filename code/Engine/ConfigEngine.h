#pragma once

#define TIME_IMPL_STL 0

// Build OS Version (name in VersionOSConst)
#if SE_PLATFORM_WINDOWS
#	define SE_WINDOWS_VERSION       SE_WINDOWS_10
#endif

#define SE_OPENGL 1
#define SE_OPENGLES 0
#define SE_VULKAN 1
#define SE_DIRECT3D11 1
#define SE_DIRECT3D12 1