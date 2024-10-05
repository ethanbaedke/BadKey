#pragma once
#include "imagelynpch.h"

#include "PreferenceManager.h"

// List of all possible names for clients
static const std::string s_Names[] = { "Ethan", "Dylan", "Morgan", "Nicole", "William", "Zoey", "Max", "Aiden", "Madelyn", "Ceci",
									   "Pheobe", "Jake", "Ally", "Loklin", "Luke", "Griffith", "Sam", "Holland", "Jon", "Matt",
									   "John", "Alex", "Nate", "Ariel", "Eric", "Jacob", "Elise", "Jordan", "Olivia", "Hudson",
									   "Josie", "Liberty", "Chelcy", "Jessie", "Jack", "Leo", "Audrey", "Bilbo Baggins", "Samwise Gamgee", "Smeagol" };
static const int s_NamesCount = 40;

namespace Imagelyn {

	class Client
	{

	private:

		std::string m_Name;

		std::vector<std::shared_ptr<Preference>> m_Preferences;

	public:

		Client();

		std::string GetName() const;
		inline const std::vector<std::shared_ptr<Preference>>& GetPreferences() const { return m_Preferences; }

		/* Prints all information about the client */
		void PrintClient() const;

	};

}

