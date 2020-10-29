#pragma once

namespace Profiler {
	// writing API

	void pause(bool paused);

	void setThreadName(const char* name);
	void showInProfiler(bool show);

	void beginBlock(const char* name_literal);
	void blockColor(u8 r, u8 g, u8 b);
	void endBlock();
	void frame();
	void pushJobInfo(u32 signal_on_finish, u32 precondition);
	void pushString(const char* value);
	void pushInt(const char* key_literal, int value);

	void beginGPUBlock(const char* name, u64 timestamp, i64 profiler_link);
	void endGPUBlock(u64 timestamp);
	void gpuMemStats(u64 total, u64 current, u64 dedicated);
	void gpuFrame();
	void link(i64 link);
	i64 createNewLinkID();

	struct FiberSwitchData {
		i32 id;
		const char* blocks[16];
		u32 count;
	};

	void beforeFiberSwitch();
	FiberSwitchData beginFiberWait(u32 job_system_signal);
	void endFiberWait(u32 job_system_signal, const FiberSwitchData& switch_data);
	float getLastFrameDuration();

	struct Scope
	{
		explicit Scope(const char* name_literal) { beginBlock(name_literal); }
		~Scope() { endBlock(); }
	};


	// reading API

	bool contextSwitchesEnabled();
	u64 frequency();

	struct ContextSwitchRecord
	{
		u32 old_thread_id;
		u32 new_thread_id;
		u64 timestamp;
		i8 reason;
	};


	struct IntRecord
	{
		const char* key;
		int value;
	};


	struct JobRecord
	{
		u32 signal_on_finish;
		u32 precondition;
	};


	struct FiberWaitRecord
	{
		i32 id;
		u32 job_system_signal;
	};


	struct GPUBlock
	{
		char name[32];
		u64 timestamp;
		i64 profiler_link;
	};

	struct GPUMemStatsBlock
	{
		u64 total;
		u64 current;
		u64 dedicated;
	};


	enum class EventType : u8
	{
		BEGIN_BLOCK,
		BLOCK_COLOR,
		END_BLOCK,
		FRAME,
		STRING,
		INT,
		BEGIN_FIBER_WAIT,
		END_FIBER_WAIT,
		CONTEXT_SWITCH,
		JOB_INFO,
		BEGIN_GPU_BLOCK,
		END_GPU_BLOCK,
		GPU_FRAME,
		GPU_MEM_STATS,
		LINK
	};

#pragma pack(1)
	struct EventHeader
	{
		u16 size;
		EventType type;
		u64 time;
	};
#pragma pack()


	struct GlobalState {
		GlobalState();
		~GlobalState();

		int threadsCount() const;
		const char* getThreadName(int idx) const;

		int local_readers_count = 0;
	};


	struct ThreadState {
		ThreadState(GlobalState& reader, int thread_idx);
		~ThreadState();

		GlobalState& reader;
		int thread_idx;

		const char* name;
		const u8* buffer;
		u32 buffer_size;
		u32 begin;
		u32 end;
		u32 thread_id;

		bool show;
	};


#define SE_CONCAT2(a, b) a ## b
#define SE_CONCAT(a, b)SE_CONCAT2(a, b)

#define PROFILE_FUNCTION() Profiler::Scope profile_scope(__FUNCTION__);
#define PROFILE_BLOCK(name) Profiler::Scope SE_CONCAT(profile_scope, __LINE__)(name);


} // namespace Profiler