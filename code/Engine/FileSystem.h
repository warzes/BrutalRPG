#pragma once

#include "Ref.h"
#include "Span.h"

template <typename T> struct Array;
template <typename T> struct Delegate;
template <typename T> struct UniquePtr;

namespace OS
{
	struct FileIterator;
	struct InputFile;
	struct OutputFile;
}

struct FileSystem
{
	using ContentCallback = Delegate<void(u64, const u8*, bool)>;

	struct AsyncHandle {
		static AsyncHandle invalid() { return AsyncHandle(0xffFFffFF); }
		explicit AsyncHandle(u32 value) : value(value) {}
		u32 value;
		bool isValid() const { return value != 0xffFFffFF; }
	};

	static UniquePtr<FileSystem> create(const char* base_path, struct IAllocator& allocator);

	virtual ~FileSystem() {}

	virtual u64 getLastModified(const char* path) = 0;
	virtual bool copyFile(const char* from, const char* to) = 0;
	virtual bool moveFile(const char* from, const char* to) = 0;
	virtual bool deleteFile(const char* path) = 0;
	virtual bool fileExists(const char* path) = 0;
	virtual OS::FileIterator* createFileIterator(const char* dir) = 0;
	virtual bool open(const char* path, Ref<OS::InputFile> file) = 0;
	virtual bool open(const char* path, Ref<OS::OutputFile> file) = 0;

	virtual void setBasePath(const char* path) = 0;
	virtual const char* getBasePath() const = 0;
	virtual void processCallbacks() = 0;
	virtual bool hasWork() = 0;
	[[nodiscard]] virtual bool makeRelative(Span<char> relative, const char* absolute) const = 0;
	virtual void makeAbsolute(Span<char> absolute, const char* relative) const = 0;

	virtual bool getContentSync(const struct Path& file, Ref<struct OutputMemoryStream> content) = 0;
	virtual AsyncHandle getContent(const Path& file, const ContentCallback& callback) = 0;
	virtual void cancel(AsyncHandle handle) = 0;
};