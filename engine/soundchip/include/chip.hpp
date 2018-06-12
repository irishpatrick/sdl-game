#pragma once

#include "sc_api.hpp"
#ifdef _WIN32
#include <portaudio/portaudio.h>
#else
#include <portaudio.h>
#endif

namespace sc {

    class Chip {
	public:
		SC_API static void init();

	private:
		static PaStreamParameters inputParams;
		static PaStreamParameters outputParams;
		static PaStream* stream;
    };

}
