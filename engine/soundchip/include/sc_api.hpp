#pragma once

#if defined(_WIN32)

#ifdef SC_EXPORTS
#define SC_API __declspec(dllexport)
#else
#define SC_API __declspec(dllimport)
#endif

#elif defined(__unix__)
#ifdef SOUNDCHIP_EXPORTS
#define SC_API __attribute__((visibility("default")))
#else
#define SC_API
#endif

#else
// do nothing and hope for the best
#define SC_API
#pragma warning Unknown dynamic link import/export semantics.
#endif
