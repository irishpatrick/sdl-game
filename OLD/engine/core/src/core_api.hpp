#pragma once

#if defined(_WIN32)

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#elif defined(__unix__)
#ifdef CORE_EXPORTS
#define CORE_API __attribute__((visibility("default")))
#else
#define CORE_API
#endif

#else
// do nothing and hope for the best
#define CORE_API
#pragma warning Unknown dynamic link import/export semantics.
#endif
