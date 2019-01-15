#pragma once

#include <cstdint>
#include <engine.hpp>
#include "ui_api.hpp"

namespace ui {

	class Widget {
	public:
		UI_API Widget();
		UI_API ~Widget();

		UI_API inline bool isVisble() { return visible; }
		UI_API inline void setVisible(bool b) { visible = b; }

		float x;
		float y;
		uint32_t width;
		uint32_t height;

	private:
		bool visible;
	};

}