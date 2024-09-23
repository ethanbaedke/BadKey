#include "Console.h"

#include <iostream>

void BadKey::Console::Log(LogType type, std::string src, std::string text)
{
	switch (type)
	{
	case LogType::MESSAGE:
		std::cout << "\033[38;2;127;127;127m";
		break;
	case LogType::WARNING:
		std::cout << "\033[38;2;255;255;0m" << "Warning: ";
		break;
	case LogType::ERROR:
		std::cout << "\033[38;2;255;0;0m" << "Error: ";
		break;
	}
	std::cout << src << " " << text << std::endl;
}
