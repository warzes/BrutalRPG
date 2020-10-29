#pragma once

#if defined(_WIN32) && !defined(SE_NO_CUSTOM_CRT)
#ifndef MCW_EM
#define _EM_OVERFLOW	0x00000004
#define _EM_ZERODIVIDE	0x00000008
#define _EM_INVALID		0x00000010
#define _EM_DENORMAL	0x00080000
#define MCW_EM			0x0008001f
#endif
#define DBL_MAX			1.7976931348623158e+308
#define DBL_MIN			2.2250738585072014e-308
#define FLT_MAX			3.402823466e+38F
#define FLT_MIN			1.175494351e-38F
#define NULL			0
#define PRId64			"lld"

extern "C" {
	typedef char* va_list;

	void* __cdecl _aligned_malloc(size_t size, size_t align);
	void __cdecl _aligned_free(void* ptr);
	void* __cdecl _aligned_realloc(void* ptr, size_t size, size_t align);
	unsigned int __cdecl _control87(unsigned int value, unsigned int mask);
	int __cdecl _stricmp(const char* str1, const char* str2);
	int __cdecl _strncmp(const char* str1, const char* str2);
	int __cdecl _strnicmp(const char* str1, const char* str2, size_t max_count);

	__declspec(noreturn) void __cdecl abort(void);
	float __cdecl acosf(float x);
	float __cdecl atan2f(float y, float x);
	double __cdecl atof(const char* str);
	int __cdecl atoi(const char* str);
	double __cdecl ceil(double x);
	float __cdecl cosf(float x);
	double __cdecl fabs(double x);
	double __cdecl floor(double _X);
#ifndef _INC_MATH
	inline float __cdecl fabsf(float x) { return (float)fabs(x); }
#ifdef SE_DEBUG
	inline float __cdecl floorf(float x) { return (float)floor(x); }
#endif
	float __cdecl ceilf(float x);
	//inline float __cdecl ceilf(float x) { return (float)ceil(x); }	
#endif
	float fmodf(float x, float y);
	double __cdecl fmod(double x, double y);
	void __cdecl free(void* ptr);
	int __cdecl _finite(double x);
	inline int __cdecl isinf(double x) { return !_finite(x); }

	double __cdecl log10(double x);
	void* __cdecl malloc(size_t size);
	const void* __cdecl memchr(const void* buf, int val, size_t max_count);
	int __cdecl memcmp(const void* buf1, const void* buf2, size_t size);
	void* __cdecl memcpy(void* dst, void const* src, size_t size); __pragma(intrinsic(memcpy))
		void* __cdecl memmove(void* dst, const void* src, size_t size);
	void* __cdecl memset(void* dst, int val, size_t size); __pragma(intrinsic(memmove))
		float __cdecl powf(float x, float y);
	double __cdecl pow(double x, double y); __pragma(intrinsic(pow))
		void __cdecl qsort(void* ptr, size_t count, size_t size, int(*cmp)(const void*, const void*));
	void* __cdecl realloc(void* ptr, size_t size);
	float __cdecl sinf(float x);
	float __cdecl sqrtf(float x);
	const char* __cdecl strchr(const char* str, int val);
	size_t __cdecl strlen(const char* str);
	int __cdecl strcmp(const char* str, const char* str2);
	char* strcpy(char* dest, const char* src);
	int __cdecl strncmp(const char* str1, const char* str2, size_t max_count);
	char* strncpy(char* dest, const char* src, size_t n);
	const char* __cdecl strstr(const char* str, const char* substr);
	float __cdecl strtof(const char* str, char** end);
	double __cdecl tan(double _X);
	float __cdecl tanf(float x);
}
#elif defined(__linux__)
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
inline int stricmp(const char* a, const char* b) { return strcasecmp(a, b); }
#endif