#include "imagelynpch.h"

#include "ConsoleManager.h"

#include <iostream>

namespace Imagelyn {

	void ConsoleManager::Log(const std::string& message, const char* color)
	{
		std::cout << color << message << std::endl;
	}

	int ConsoleManager::GetInt(unsigned int lower, unsigned int upper, const std::string& prompt, const char* color)
	{
		std::cout << color << prompt << ": ";

		// Get user input
		std::string input;
		std::getline(std::cin, input);

		// Input is empty
		if (input.length() == 0)
		{
			BK_WARNING(std::string("Please input your selection"));
			return GetInt(lower, upper, prompt, color);
		}

		unsigned int value = 0;

		// Count the value of the input string while checking that it only contains numbers
		for (int i = 0; i < input.length(); i++)
		{
			char c = input[i];
			if (c >= '0' && c <= '9')
			{
				value += (c - '0') * (pow(10, input.length() - i - 1));
			}
			else
			{
				BK_WARNING("Your input contains invalid characters, please use digits 0-9");
				return GetInt(lower, upper, prompt, color);
			}
		}

		if (value >= lower && value <= upper)
		{
			// If the input value is within our bounds, return it
			CONSOLE_CLEAR();
			return value;
		}
		else
		{
			// If the input value is out of our bounds, try again
			BK_WARNING(std::string("Please input a value between ") + std::to_string(lower) + " and " + std::to_string(upper));
			return GetInt(lower, upper, prompt, color);
		}
	}

	void ConsoleManager::BreakLine()
	{
		std::cout << std::endl;
	}

}