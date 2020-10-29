#pragma once

#ifdef _WIN32
#include <xmmintrin.h>
#else
#include <math.h>
#endif

#ifdef _WIN32
using float4 = __m128;


inline float4 f4LoadUnaligned(const void* src)
{
	return _mm_loadu_ps((const float*)(src));
}


inline float4 f4Load(const void* src)
{
	return _mm_load_ps((const float*)(src));
}


inline float4 f4Splat(float value)
{
	return _mm_set_ps1(value);
}


inline void f4Store(void* dest, float4 src)
{
	_mm_store_ps((float*)dest, src);
}


inline int f4MoveMask(float4 a)
{
	return _mm_movemask_ps(a);
}


inline float4 f4Add(float4 a, float4 b)
{
	return _mm_add_ps(a, b);
}


inline float4 f4Sub(float4 a, float4 b)
{
	return _mm_sub_ps(a, b);
}


inline float4 f4Mul(float4 a, float4 b)
{
	return _mm_mul_ps(a, b);
}


inline float4 f4Div(float4 a, float4 b)
{
	return _mm_div_ps(a, b);
}


inline float4 f4Rcp(float4 a)
{
	return _mm_rcp_ps(a);
}


inline float4 f4Sqrt(float4 a)
{
	return _mm_sqrt_ps(a);
}


inline float4 f4Rsqrt(float4 a)
{
	return _mm_rsqrt_ps(a);
}


inline float4 f4Min(float4 a, float4 b)
{
	return _mm_min_ps(a, b);
}


inline float4 f4Max(float4 a, float4 b)
{
	return _mm_max_ps(a, b);
}

#else 
struct float4
{
	float x, y, z, w;
};


inline float4 f4LoadUnaligned(const void* src)
{
	return *(const float4*)src;
}


inline float4 f4Load(const void* src)
{
	return *(const float4*)src;
}


inline float4 f4Splat(float value)
{
	return { value, value, value, value };
}


inline void f4Store(void* dest, float4 src)
{
	(*(float4*)dest) = src;
}


inline int f4MoveMask(float4 a)
{
	return (a.w < 0 ? (1 << 3) : 0) |
		(a.z < 0 ? (1 << 2) : 0) |
		(a.y < 0 ? (1 << 1) : 0) |
		(a.x < 0 ? 1 : 0);
}


inline float4 f4Add(float4 a, float4 b)
{
	return{
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	};
}


inline float4 f4Sub(float4 a, float4 b)
{
	return{
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	};
}


inline float4 f4Mul(float4 a, float4 b)
{
	return{
		a.x * b.x,
		a.y * b.y,
		a.z * b.z,
		a.w * b.w
	};
}


inline float4 f4Div(float4 a, float4 b)
{
	return{
		a.x / b.x,
		a.y / b.y,
		a.z / b.z,
		a.w / b.w
	};
}


inline float4 f4Rcp(float4 a)
{
	return{
		1 / a.x,
		1 / a.y,
		1 / a.z,
		1 / a.w
	};
}


inline float4 f4Sqrt(float4 a)
{
	return{
		(float)sqrt(a.x),
		(float)sqrt(a.y),
		(float)sqrt(a.z),
		(float)sqrt(a.w)
	};
}


inline float4 f4Rsqrt(float4 a)
{
	return{
		1 / (float)sqrt(a.x),
		1 / (float)sqrt(a.y),
		1 / (float)sqrt(a.z),
		1 / (float)sqrt(a.w)
	};
}


inline float4 f4Min(float4 a, float4 b)
{
	return{
		a.x < b.x ? a.x : b.x,
		a.y < b.y ? a.y : b.y,
		a.z < b.z ? a.z : b.z,
		a.w < b.w ? a.w : b.w
	};
}


inline float4 f4Max(float4 a, float4 b)
{
	return{
		a.x > b.x ? a.x : b.x,
		a.y > b.y ? a.y : b.y,
		a.z > b.z ? a.z : b.z,
		a.w > b.w ? a.w : b.w
	};
}

#endif