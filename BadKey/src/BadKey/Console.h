#pragma once
#include "bkpch.h"

#include "Engine.h"

#define BK_MESSAGE(x)			BadKey::Console::Log(BadKey::LogType::MESSAGE, "[Client]", x)
#define BK_WARNING(x)			BadKey::Console::Log(BadKey::LogType::WARNING, "[Client]", x)
#define BK_ERROR(x)				BadKey::Console::Log(BadKey::LogType::ERROR, "[Client]", x)

#define BK_ENGINE_MESSAGE(x)	BadKey::Console::Log(BadKey::LogType::MESSAGE, "[Engine]", x)
#define BK_ENGINE_WARNING(x)	BadKey::Console::Log(BadKey::LogType::WARNING, "[Engine]", x)
#define BK_ENGINE_ERROR(x)		BadKey::Console::Log(BadKey::LogType::ERROR, "[Engine]", x)

namespace BadKey {

	enum LogType : char
	{
		MESSAGE,
		WARNING,
		ERROR
	};

	class BK_API Console
	{

	public:

		static void Log(LogType type, std::string src, std::string text);

	};

}