#pragma once

template <typename T>
struct Span
{
	Span() : m_begin(nullptr), m_end(nullptr) {}
	Span(T* begin, u32 len) : m_begin(begin), m_end(begin + len) {}
	Span(T* begin, T* end) : m_begin(begin), m_end(end) {}
	template <int N> explicit Span(T(&value)[N]) : m_begin(value), m_end(m_begin + N) {}
	T& operator[](u32 idx) const { ASSERT(m_begin + idx < m_end); return m_begin[idx]; }
	operator Span<const T>() const { return Span<const T>(m_begin, m_end); }
	Span fromLeft(u32 count) const { return Span(m_begin + count, m_end); }

	u32 length() const { return u32(m_end - m_begin); }

	T* begin() const { return m_begin; }
	T* end() const { return m_end; }

	T* m_begin;
	T* m_end;
};