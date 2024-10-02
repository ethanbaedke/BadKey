#pragma once

#include "bkpch.h"
#include "Engine.h"

namespace BadKey {

	class BK_API IPrintable
	{

	public:

		virtual std::string GetPrintable() const = 0;

	};

}