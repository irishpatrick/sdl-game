#include "asynctimer.hpp"
#ifdef __linux__
    #include <unistd.h>
#endif

namespace engine {

AsyncTimer::AsyncTimer() {

}

AsyncTimer::~AsyncTimer() {

}

void AsyncTimer::start(uint32_t d) {

}

bool AsyncTimer::poll() {
    return false;
}

}
