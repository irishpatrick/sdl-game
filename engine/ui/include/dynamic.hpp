#pragma once

#if defined(_WIN32)
    #ifdef UI_EXPORTS
        #define UI_API __declspec(dllexport)
    #else
        #define UI_API __declspec(dllimport)
    #endif
#elif defined(__unix__)
    #ifdef UI_EXPORTS
        #define UI_API __attribute__((visibility("default")))
    #else
        #define UI_API
    #endif
#else
    // do nothing and hope for the best
    #define UI_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
