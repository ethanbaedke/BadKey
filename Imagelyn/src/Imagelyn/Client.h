#pragma once
#include "imagelynpch.h"

#include "Preference.h"

namespace Imagelyn {

	class Client
	{

	private:

		/* Name of the client */
		std::string m_Name;

		/* Preferences this client has */
		std::vector<std::shared_ptr<Preference>> m_Preferences;

	public:

		Client();

		/* Prints all information about the client */
		void PrintClient() const;

		inline const std::string& GetName() const { return m_Name; }
		inline const std::vector<std::shared_ptr<Preference>>& GetPreferences() const { return m_Preferences; }

	};

	class ClientManager
	{

	private:

		/* List of all names clients can have */
		static std::vector<std::string> m_Names;

	public:

		/* Adds a name as a possible name to be picked for a client */
		static void AddName(const std::string& name);

		/* Get a random name from the list of names clients can have */
		static const std::string& GetName();

		/*
		* Returns true if the client manager is ready for the game to be played
		* This returns false in cases where the client manager doesn't have enough valid names for the game to run correctly
		*/
		static bool ValidClientInit();

	};

}

