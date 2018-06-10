#include "chip.hpp"
#include <iostream>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace sc {

	ALCdevice* Chip::dev = nullptr;
	ALCcontext* Chip::ctx = nullptr;
	ALuint Chip::buf = 0;
	ALuint Chip::src = 0;

	void Chip::init() {
		const char* defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
		std::cout << "default device: " << defname << std::endl;

		dev = alcOpenDevice(defname);
		ctx = alcCreateContext(dev, NULL);
		alcMakeContextCurrent(ctx);

		alGenBuffers(1, &buf);
		
		alGenSources(1, &src);
		//alSourcei(src, AL_BUFFER, buf);
	}

	void Chip::play(float freq, int seconds) {
		//float freq = 440.0f;
		//int seconds = 4;
		unsigned sample_rate = 22050;
		size_t buf_size = seconds * sample_rate;

		short* samples;
		samples = new short[buf_size];
		for (int i = 0; i < buf_size; i++) {
			samples[i] = 32760 * sin((2.f * float(M_PI) * freq) / sample_rate * i);
		}

		alBufferData(buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);

		alSourcei(src, AL_BUFFER, buf);
		alSourcePlay(src);
	}

	void Chip::destroy() {
		alcMakeContextCurrent(NULL);
		alcDestroyContext(ctx);
		alcCloseDevice(dev);
	}
}