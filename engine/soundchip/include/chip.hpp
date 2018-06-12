#pragma once

#include "sc_api.hpp"
#include <portaudio/portaudio.h>

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
