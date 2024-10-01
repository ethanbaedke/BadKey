#include "PreferenceManager.h"

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


}