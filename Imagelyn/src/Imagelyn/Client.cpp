#include "imagelynpch.h"

#include "Client.h"
#include "ConsoleManager.h"

namespace Imagelyn {

	// Declare static variables
	std::vector<std::string> ClientManager::m_Names;

	Client::Client()
	{
		// Give the client a random name
		m_Name = ClientManager::GetName();

		// Give a client random preferences
		while (m_Preferences.size() < 3)
		{
			std::shared_ptr<Preference> pref = PreferenceManager::GetRandomPreference();

			// Make sure there are no duplicate preferences
			int f = 0;
			while (f < m_Preferences.size() && m_Preferences[f] != pref)
				f++;
			if (f == m_Preferences.size())
				m_Preferences.push_back(pref);
		}
	}

	void Client::PrintClient() const
	{
		ConsoleManager::Log("Name: " + m_Name, COLOR_CLIENT);
		for (int i = 0; i < 3; i++)
		{
			ConsoleManager::Log("Preference: " + m_Preferences[i]->GetName(), COLOR_CLIENT);
		}
		ConsoleManager::BreakLine();
	}

	void ClientManager::AddName(const std::string& name)
	{
		m_Names.push_back(name);
	}

	const std::string& ClientManager::GetName()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> nameDist(0, m_Names.size() - 1);
		int nameIndex = nameDist(gen);
		return m_Names[nameIndex];
	}

	bool ClientManager::ValidClientInit()
	{
		// Three names must be present so three clients with unique names can be chosen
		if (m_Names.size() < 3)
		{
			BK_ERROR("At least three names must be defined for a valid game");
			return false;
		}
		return true;
	}

}
