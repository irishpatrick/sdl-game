#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Texture.hpp"
#include <string>
#include <vector>

namespace engine
{
	class ScrollingText
	{
	public:
		CORE_API ScrollingText()
		{
			t = nullptr;
		}

		CORE_API ~ScrollingText()
		{

		}

		CORE_API void init(Context&, const std::string&);
		CORE_API void update();
		CORE_API void draw(Context&);

	private:
		Texture* t;
	};
}