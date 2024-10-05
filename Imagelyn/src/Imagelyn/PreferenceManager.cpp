#include "imagelynpch.h"

#include "PreferenceManager.h"

#include <BadKey.h>

namespace Imagelyn {

	std::vector<std::shared_ptr<Preference>> PreferenceManager::m_Preferences;

	Preference::Preference(std::string name)
		: m_Name(name)
	{
	}

	std::string Preference::GetPrintable() const
	{
		return "Preference: " + m_Name;
	}

	bool PreferenceManager::AddPreference(std::shared_ptr<Preference> preference)
	{
		// Make sure the preference being added doesn't already exist
		if (GetPreferenceByName(preference->GetName()) == nullptr)
		{
			m_Preferences.push_back(preference);
			return true;
		}
		else
		{
			return false;
		}
	}

	std::shared_ptr<Preference> PreferenceManager::GetPreferenceByName(const std::string& preferenceName)
	{
		int i = 0;
		while (i < m_Preferences.size() && m_Preferences[i]->GetName() != preferenceName)
			i++;
		if (i < m_Preferences.size())
			return m_Preferences[i];
		else
			return nullptr;
	}

	std::shared_ptr<Preference> PreferenceManager::GetRandomPreference()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> nameDist(0, m_Preferences.size() - 1);
		int index = nameDist(gen);
		return m_Preferences[index];
	}

	bool PreferenceManager::ValidPreferenceInit()
	{
		if (m_Preferences.size() < 3)
		{
			BK_ERROR("At least three preferences must be defined for a valid game");
			return false;
		}
		return true;
	}


}