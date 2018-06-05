#include "timer.hpp"

namespace engine {

	Timer::Timer() {
		duration_ = 0.0;
		then_ = 0;
		now_ = 0;
	}

	Timer::~Timer() {

	}

	void Timer::SetInterval(double ms) {
		duration_ = ms;
		then_ = SDL_GetTicks();
	}

	void Timer::Reset() {
		then_ = SDL_GetTicks();
	}

	bool Timer::Tick() {
		now_ = SDL_GetTicks();
		double delta = now_ - then_;
		if (delta >= duration_) {
			then_ = now_;
			return true;
		}
		return false;
	}

}
