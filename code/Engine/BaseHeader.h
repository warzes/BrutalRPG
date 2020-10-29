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
#include "AssertMacros.h"

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
#include <random>

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
//#	include <SimpleWindows.h>
#	include <Windows.h>
#	include <VersionHelpers.h>
#	include <wrl.h> // Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#	include <shellapi.h>
#	include <strsafe.h>
#	include <immintrin.h>
#	include <ShlObj.h>
#	include <evntcons.h>
#	undef near
#	undef far
#	undef NEAR
#	undef FAR
#else
#	include <sys/time.h>
#endif // SE_PLATFORM_*
SE_PRAGMA_WARNING_POP


//-----------------------------------------------------------------------------
// Temp
//-----------------------------------------------------------------------------
typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef unsigned int u32;
#ifdef _WIN32
typedef long long i64;
typedef unsigned long long u64;
#else	
typedef long i64;
typedef unsigned long u64;
#endif
typedef u64 uintptr;

static_assert(sizeof(uintptr) == sizeof(void*), "Incorrect size of uintptr");
static_assert(sizeof(i64) == 8, "Incorrect size of i64");
static_assert(sizeof(i32) == 4, "Incorrect size of i32");
static_assert(sizeof(i16) == 2, "Incorrect size of i16");
static_assert(sizeof(i8) == 1, "Incorrect size of i8");

const u32 MAX_PATH_LENGTH = 260;

struct EntityRef;

struct EntityPtr
{
	EntityPtr() : index(-1) {}
	EntityPtr(i32 index) : index(index) {}
	i32 index;
	bool operator==(const EntityPtr& rhs) const { return rhs.index == index; }
	bool operator<(const EntityPtr& rhs) const { return rhs.index < index; }
	bool operator>(const EntityPtr& rhs) const { return rhs.index > index; }
	bool operator!=(const EntityPtr& rhs) const { return rhs.index != index; }
	bool isValid() const { return index >= 0; }
	inline explicit operator EntityRef() const;
};

struct EntityRef
{
	int index;
	bool operator==(const EntityRef& rhs) const { return rhs.index == index; }
	bool operator<(const EntityRef& rhs) const { return rhs.index < index; }
	bool operator>(const EntityRef& rhs) const { return rhs.index > index; }
	bool operator!=(const EntityRef& rhs) const { return rhs.index != index; }
	operator EntityPtr() const { return { index }; }
};

struct ComponentType
{
	enum { MAX_TYPES_COUNT = 64 };

	int index;
	bool operator==(const ComponentType& rhs) const { return rhs.index == index; }
	bool operator<(const ComponentType& rhs) const { return rhs.index < index; }
	bool operator>(const ComponentType& rhs) const { return rhs.index > index; }
	bool operator!=(const ComponentType& rhs) const { return rhs.index != index; }
};
const ComponentType INVALID_COMPONENT_TYPE = { -1 };
const EntityPtr INVALID_ENTITY = { -1 };

template <typename T, u32 count> constexpr u32 lengthOf(const T(&)[count])
{
	return count;
};

#pragma pack(1)
struct Color {
	Color() {}
	Color(u32 abgr) {
		r = u8(abgr & 0xff);
		g = u8((abgr >> 8) & 0xff);
		b = u8((abgr >> 16) & 0xff);
		a = u8((abgr >> 24) & 0xff);
	}

	Color(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

	u32 abgr() const { return ((u32)a << 24) | ((u32)b << 16) | ((u32)g << 8) | (u32)r; }

	u8 r;
	u8 g;
	u8 b;
	u8 a;

	static constexpr u32 RED = 0xff0000ff;
	static constexpr u32 GREEN = 0xff00ff00;
	static constexpr u32 BLUE = 0xffff0000;
	static constexpr u32 BLACK = 0xff000000;
	static constexpr u32 WHITE = 0xffFFffFF;
};

#pragma pack()

struct Time {
	Time() {}
	static Time fromSeconds(float time) {
		//ASSERT(time >= 0);
		return { u32(time * ONE_SECOND) };
	}
	float seconds() const { return float(value / double(ONE_SECOND)); }
	Time operator+(const Time& rhs) const { return { value + rhs.value }; }
	void operator+=(const Time& rhs) { value += rhs.value; }
	bool operator<(const Time& rhs) const { return value < rhs.value; }
	bool operator<=(const Time& rhs) const { return value <= rhs.value; }
	Time operator%(const Time& rhs) const { return { value % rhs.value }; }
	u32 raw() const { return value; }

private:
	Time(u32 v) : value(v) {}
	u32 value;
	static constexpr u32 ONE_SECOND = 1 << 15;
};

inline EntityPtr::operator EntityRef() const
{
	//ASSERT(isValid());
	return { index };
}