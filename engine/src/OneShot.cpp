#include "OneShot.hpp"

namespace engine {

	OneShot::OneShot() {
		state = false;
		reset = false;
	}

	OneShot::~OneShot() {

	}

	void OneShot::setPointer(bool* b)
	{
		ptr = b;
	}

	void OneShot::check(bool b) {
		if (reset) {
			state = false;
		}

		if (b && !reset) {
			state = true;
			reset = true;
		}

		if (!b && reset) {
			reset = false;
		}
	}

	bool OneShot::altFire()
	{
		if (reset)
		{
			state = false;
		}

		if (*ptr && !reset)
		{
			state = true;
			reset = true;
		}

		if (!*ptr && reset)
		{
			reset = false;
		}

		return state;
	}

	bool OneShot::fire() {
		return state;
	}

}
