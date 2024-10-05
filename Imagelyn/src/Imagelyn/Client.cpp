#include "imagelynpch.h"

#include "Client.h"
#include "ConsoleManager.h"

namespace Imagelyn {

	Client::Client()
	{
		// Give the client a random name
		// THIS IS HORRIBLE!!! WHY DID I EVER WRITE THIS CODE?!?! Allow the user to input a name list to be loaded instead
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> nameDist(0, s_NamesCount - 1);
		int nameIndex = nameDist(gen);
		m_Name = s_Names[nameIndex];

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

	std::string Client::GetName() const
	{
		return m_Name;
	}

	void Client::PrintClient() const
	{
		ConsoleManager::Log("Name: " + m_Name, COLOR_CLIENT);
		for (int i = 0; i < 3; i++)
		{
			ConsoleManager::Log(m_Preferences[i]->GetPrintable(), COLOR_CLIENT);
		}
		ConsoleManager::BreakLine();
	}

}
