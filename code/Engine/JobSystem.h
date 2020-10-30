#pragma once

#include "Atomic.h"

struct IAllocator;

namespace JobSystem 
{

	using SignalHandle = u32;
	constexpr u8 ANY_WORKER = 0xff;
	constexpr u32 INVALID_HANDLE = 0xffFFffFF;

	bool init(u8 workers_count, IAllocator& allocator);
	void shutdown();
	u8 getWorkersCount();

	void enableBackupWorker(bool enable);

	void incSignal(SignalHandle* signal);
	void decSignal(SignalHandle signal);

	void run(void* data, void(*task)(void*), SignalHandle* on_finish);
	void runEx(void* data, void (*task)(void*), SignalHandle* on_finish, SignalHandle precondition, u8 worker_index);
	void wait(SignalHandle waitable);
	inline bool isValid(SignalHandle waitable) { return waitable != INVALID_HANDLE; }


	template <typename F>
	void runOnWorkers(const F& f)
	{
		SignalHandle signal = JobSystem::INVALID_HANDLE;
		for (int i = 0, c = getWorkersCount(); i < c; ++i) {
			JobSystem::run((void*)&f, [](void* data) {
				(*(const F*)data)();
				}, &signal);
		}
		wait(signal);
	}


	template <typename F>
	void forEach(i32 count, i32 step, const F& f)
	{
		if (count == 0) return;
		if (count <= step) {
			f(0, count);
			return;
		}

		volatile i32 offset = 0;

		JobSystem::runOnWorkers([&]() {
			for (;;) {
				const i32 idx = atomicAdd(&offset, step);
				if (idx >= count) break;
				i32 to = idx + step;
				to = to > count ? count : to;
				f(idx, to);
			}
			});
	}

} // namespace JobSystem