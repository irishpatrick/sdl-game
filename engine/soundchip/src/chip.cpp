#include "chip.hpp"
#include <iostream>
#include <cstdlib>

namespace sc {

	ALCdevice* Chip::dev = nullptr;
	ALCcontext* Chip::ctx = nullptr;

	void Chip::init() {
		const char* defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
		std::cout << "default device: " << defname << std::endl;

		dev = alcOpenDevice(defname);
		ctx = alcCreateContext(dev, NULL);
		alcMakeContextCurrent(ctx);
	}

	void Chip::destroy() {
		alcMakeContextCurrent(NULL);
		alcDestroyContext(ctx);
		alcCloseDevice(dev);
	}
}