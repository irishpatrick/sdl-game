#pragma once

#include <string>

namespace core {

    class MsgBox {
    public:
        static int show(int, int, std::string&, std::string&);

        static const int INFO = 0;
        static const int WARNING = 1;
        static const int ERROR = 2;
        static const int QUESTION = 3;

        static const int OK = 4;
        static const int OKCANCEL = 5;
        static const int YESNO = 6;
    };

}