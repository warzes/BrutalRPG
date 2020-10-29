#pragma once

// use this instead non-const reference parameter to show intention
template <typename T>
struct Ref {
	Ref(const Ref<T>& value) : value(value.value) {}
	explicit Ref(T& value) : value(value) {}
	operator T& () { return value; }
	T* operator->() { return &value; }
	void operator =(const Ref<T>& rhs) { value = rhs.value; }
	void operator =(const T& rhs) { value = rhs; }
	template <typename T2> void operator =(const T2& rhs) { value = rhs; }
	T& value;
};