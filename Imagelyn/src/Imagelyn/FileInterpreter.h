#pragma once
#include "imagelynpch.h"

#include "Location.h"

namespace Imagelyn {

	class FileInterpreter
	{

	private:

		/* Holds the current location info is being read about */
		static std::shared_ptr<Location> m_CurrentLocation;

		/* Holds the current activity info is being read about */
		static std::shared_ptr<Activity> m_CurrentActivity;

	public:

		/* Loads a file of keywords */
		static bool Load(std::string path);

	private:

		/* Returns whether or not the input character is an alphanumeric character in the ascii table */
		static bool IsAlphanumeric(char character);

		/* The next set of text in the file should be read and interpruted as a keyword */
		static const std::string ParseKeyword(std::ifstream& file, std::string& errorMessage);

		/* The next set of text in the file should be read and interpruted as a string */
		static const std::string ParseString(std::ifstream& file, std::string& errorMessage);

		/* Takes in a keyword and operates on it accordingly */
		static void HandleKeyword(const std::string& keyword, std::ifstream& file, std::string& errorMessage);

	};

}