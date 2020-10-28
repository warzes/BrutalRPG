#pragma once

#if SE_DEBUG
#	define SE_ASSERT(x, txt) assert(x && txt)
#else
#	define SE_ASSERT(x, txt)
#endif