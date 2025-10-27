#pragma once

#include <signal.h>

#define TZ_ENABLE_ASSERTS

#ifdef TZ_ENABLE_ASSERTS

#define TZ_ASSERT(x, ...) { if(!(x)) { TZ_ERROR(__VA_ARGS__);  raise(SIGTRAP); } }
#define TZ_CORE_ASSERT(x, ...) { if(!(x)) { TZ_CORE_ERROR(__VA_ARGS__);  raise(SIGTRAP); } }

#else

#define TZ_ASSERT(x, ...)
#define TZ_CORE_ASSERT(x, ...)

#endif

#define BIT(x) (1 << x)
