#pragma once

#include "sc_api.hpp"

#include <al.h>
#include <alc.h>
#include <AL/alut.h>

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