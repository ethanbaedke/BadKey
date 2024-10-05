#pragma once
#include "imagelynpch.h"

#include "LocationManager.h"

namespace Imagelyn {

	class FileInterpreter
	{

	private:

		static std::shared_ptr<Location> m_CurrentLocation;
		static std::shared_ptr<Activity> m_CurrentActivity;

	public:

		static bool Load(std::string path);

	private:

		/* Returns whether or not the input character is an alphanumeric character in the ascii table */
		static bool IsAlphanumeric(char character);

		/* The next set of text in the file should be read and interpruted as a keyword */
		static std::string ParseKeyword(std::ifstream& file, std::string& errorMessage);

		/* The next set of text in the file should be read and interpruted as a string */
		static std::string ParseString(std::ifstream& file, std::string& errorMessage);

		/* Takes in a keyword and operates on it accordingly */
		static void HandleKeyword(const std::string& keyword, std::ifstream& file, std::string& errorMessage);

	};

}