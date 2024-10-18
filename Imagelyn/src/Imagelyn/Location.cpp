#include "imagelynpch.h"

#include "Location.h"

namespace Imagelyn {

	// Declare static variables
	std::vector<std::shared_ptr<Location>> LocationManager::m_Locations;

	Location::Location(std::string name)
		: m_Name(name), m_Activities(std::vector<std::shared_ptr<Activity>>())
	{
	}

	void Location::AddActivity(const std::shared_ptr<Activity> activity)
	{
		m_Activities.push_back(activity);
	}

	Activity::Activity(std::string name)
		: m_Name(name)
	{
	}

	const std::vector<std::shared_ptr<Preference>> Activity::GetPositivePreferences() const
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_PositiveHints)
		{
			prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	const std::vector<std::shared_ptr<Preference>> Activity::GetNegativePreferences() const
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_NegativeHints)
		{
			prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	void Activity::UnlockPositiveHint(std::shared_ptr<Preference> preference)
	{
		int i = 0;
		while (i < m_PositiveHints.size() && m_PositiveHints[i].m_Preference != preference)
			i++;
		if (i < m_PositiveHints.size())
			m_PositiveHints[i].m_Unlocked = true;
	}

	void Activity::UnlockNegativeHint(std::shared_ptr<Preference> preference)
	{
		int i = 0;
		while (i < m_NegativeHints.size() && m_NegativeHints[i].m_Preference != preference)
			i++;
		if (i < m_PositiveHints.size())
			m_NegativeHints[i].m_Unlocked = true;
	}

	const std::vector<std::shared_ptr<Preference>> Activity::GetPositiveUnlockedHints() const
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_PositiveHints)
		{
			if (h.m_Unlocked)
				prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	const std::vector<std::shared_ptr<Preference>> Activity::GetNegativeUnlockedHints() const
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_NegativeHints)
		{
			if (h.m_Unlocked)
				prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	void LocationManager::AddLocation(std::shared_ptr<Location> location)
	{
		m_Locations.push_back(location);
	}

}
