#pragma once

#ifdef TZ_ENABLE_ASSERTS

#define TZ_ASSERT(x, ...) { if(!(x)) { TZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TZ_CORE_ASSERT(x, ...) { if(!(x)) { TZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

#define TZ_ASSERT(x, ...)
#define TZ_CORE_ASSERT(x, ...)

#endif

#define BIT(x) (1 << x)
