#pragma once

#include "ui_api.hpp"

#include <engine.hpp>

namespace ui {

    class Config {
	public:
		UI_API static engine::ImageFont& getFont();

	private:
		static engine::ImageFont font;
    };

}