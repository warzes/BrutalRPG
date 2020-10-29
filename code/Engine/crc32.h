#pragma once

u32 crc32(const void* data, u32 length);
u32 crc32(const char* str);
u32 continueCrc32(u32 original_crc, const char* str);
u32 continueCrc32(u32 original_crc, const void* data, u32 length);