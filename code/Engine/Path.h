#pragma once

#include "Span.h"

struct PathInfo
{
	explicit PathInfo(const char* path);

	char m_extension[10];
	char m_basename[MAX_PATH_LENGTH];
	char m_dir[MAX_PATH_LENGTH];
};

struct Path
{
public:
	static void normalize(const char* path, Span<char> out);
	static void getDir(Span<char> dir, const char* src);
	static void getBasename(Span<char> basename, const char* src);
	static void getExtension(Span<char> extension, Span<const char> src);
	static bool hasExtension(const char* filename, const char* ext);
	static bool replaceExtension(char* path, const char* ext);

public:
	Path();
	explicit Path(const char* path);

	void operator=(const char* rhs);
	bool operator==(const Path& rhs) const;
	bool operator!=(const Path& rhs) const;

	i32 length() const;
	u32 getHash() const { return m_hash; }
	const char* c_str() const { return m_path; }
	bool isValid() const { return m_path[0] != '\0'; }

private:
	char m_path[MAX_PATH_LENGTH];
	u32 m_hash;
};