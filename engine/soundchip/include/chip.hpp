#pragma once

#include "sc_api.hpp"

#ifdef _WIN32

#include <al.h>
#include <alc.h>
#include <AL/alut.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

namespace sc {

	class Chip {

	public:
		SC_API static void init();
		SC_API static void destroy();
		SC_API static void play(float, int);
		
	private:
		static ALCdevice* dev;
		static ALCcontext* ctx;
		static ALuint buf;
		static ALuint src;
	};

}
