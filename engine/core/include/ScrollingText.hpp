#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Texture.hpp"
#include <string>

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

	private:
		Texture* t;
	};
}