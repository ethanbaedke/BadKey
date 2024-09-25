#pragma once

#include "Engine.h"

#include <string>

namespace BadKey {

	class BK_API IPrintable
	{

	public:

		virtual std::string GetPrintable() const = 0;

	};

}