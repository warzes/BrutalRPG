#pragma once

#if SE_DEBUG
#	define SE_ASSERT(x, txt) assert(x && txt)
#else
#	define SE_ASSERT(x, txt)
#endif

#ifndef ASSERT
#if SE_DEBUG
#ifdef _WIN32
#else
#define SE_DEBUG_BREAK()  raise(SIGTRAP) 
#endif
//#define ASSERT(x) do { const volatile bool se_assert_b____ = !(x); if(se_assert_b____) SE_DEBUG_BREAK(); } while (false)
#define ASSERT(x) assert(x)
#else
#ifdef _WIN32		
#define ASSERT(x) __assume(x)
#else
#define ASSERT(x) { false ? (void)(x) : (void)0; }
#endif
#endif
#endif