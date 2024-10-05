#pragma once
#include "imagelynpch.h"

#define COLOR_DEFAULT	"\033[38;2;104;174;212m"
#define COLOR_CLIENT	"\033[38;2;204;163;41m"
#define COLOR_ACTIVITY	"\033[38;2;36;179;167m"
#define COLOR_POSITIVE	"\033[38;2;46;153;55m"
#define COLOR_NEGATIVE	"\033[38;2;179;54;54m"

#ifdef PLATFORM_WINDOWS
	#define CONSOLE_CLEAR() system("cls")
#elif defined(PLATFORM_MACOSX)
	#define CONSOLE_CLEAR() system("clear")
#endif

namespace Imagelyn {

	class ConsoleManager
	{

	public:

		/* Outputs a message to the console, takes in one of the defined colors in this file */
		static void Log(const std::string& message, const char* color);

		/* Gets a single integer input from the user between the input bounds */
		static int GetInt(unsigned int lower, unsigned int upper, const std::string& prompt, const char* color);

		/* Gets text input from the user, displays the input prompt prior to retrieving input */
		static std::string GetString(const std::string& prompt, const char* color);

		/* Adds a break in the console */
		static void BreakLine();

	};

}