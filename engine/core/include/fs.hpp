#pragma once

#include <experimental/filesystem>

namespace engine
{
    class Fs
    {

    };
}

/*#if defined(_WIN32)
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <string>

namespace engine
{

    class Fs
    {
    public:
        #if defined(_WIN32)
        static const char DEFAULT_SEPARATOR = '\\';
        #elif defined(__unix__)
        static const char DEFAULT_SEPARATOR = '/';
        #endif

        inline static bool Fs::isDir(const std::string& path)
        {
            struct stat info;
            stat(info, path.c_str());
            return S_ISDIR(info.st_mode);
        }

        inline static std::string join(const std::string& a, const std::string& b)
        {
            int alast = a.size() - 1;
            int blast = b.size() - 1;
            std::string part_a;
            std::string part_b;
            if (a[alast] == '\\')
            {
                part_a = a;
                part_a[alast] = '/';
            }
            if (a[alast] != '/')
            {
                part_a = a + '/';
            }

            return part_a + part_b;
        }

        inline static bool Fs::isFile(const std::string& path)
        {
            struct stat info;
            stat(info, path.c_str());
            return S_ISREG(info.st_mode);
        }

    };

}*/
