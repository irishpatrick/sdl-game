#include "chip.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace sc {

	PaStream* Chip::stream = nullptr;
	PaStreamParameters Chip::inputParams;
	PaStreamParameters Chip::outputParams;

	void Chip::init() {
		PaError err;
		int numDevices;
		const PaDeviceInfo* devInfo;

		err = Pa_Initialize();
		if (err != paNoError) {
			std::cout << "error: Pa_Initialize retured " << err << std::endl;
			return;
		}
		std::cout << "PortAudio version: " << Pa_GetVersion() << std::endl;
		std::cout << "Version text: " << Pa_GetVersionInfo()->versionText << std::endl;

		inputParams.device = Pa_GetDefaultInputDevice();
		if (inputParams.device = paNoDevice) {
			std::cout << "no in device" << std::endl;
			return;
		}
		inputParams.channelCount = 2;
		inputParams.sampleFormat = paFloat32;
		inputParams.suggestedLatency = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
		inputParams.hostApiSpecificStreamInfo = NULL;
	}

}