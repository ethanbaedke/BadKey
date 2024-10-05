#include "imagelynpch.h"

#include "LocationManager.h"

namespace Imagelyn {

	std::vector<std::shared_ptr<Location>> LocationManager::m_Locations;

	Location::Location(std::string name)
		: m_Name(name), m_Activities(std::vector<std::shared_ptr<Activity>>())
	{
	}

	void Location::AddActivity(const std::shared_ptr<Activity> activity)
	{
		m_Activities.push_back(activity);
	}

	std::string Location::GetPrintable() const
	{
		// Debug the name of this location
		std::string debug = "Location: " + m_Name;

		// Debug all activites of this location
		for (const std::shared_ptr<Activity> act : m_Activities)
			debug += "\n" + act->GetPrintable();

		return debug;
	}

	Activity::Activity(std::string name)
		: m_Name(name), m_Description("(none)")
	{
	}

	std::vector<std::shared_ptr<Preference>> Activity::GetPositivePreferences()
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_PositiveHints)
		{
			prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	std::vector<std::shared_ptr<Preference>> Activity::GetNegativePreferences()
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

	std::vector<std::shared_ptr<Preference>> Activity::GetPositiveUnlockedHints()
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_PositiveHints)
		{
			if (h.m_Unlocked)
				prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	std::vector<std::shared_ptr<Preference>> Activity::GetNegativeUnlockedHints()
	{
		std::vector<std::shared_ptr<Preference>> prefs;
		for (const Hint& h : m_NegativeHints)
		{
			if (h.m_Unlocked)
				prefs.push_back(h.m_Preference);
		}
		return prefs;
	}

	std::string Activity::GetPrintable() const
	{
		// Debug the name of this activity
		std::string debug = "Activity: " + m_Name;
		
		// Debug the description of this activity
		debug += "\n" + std::string("Description: ") + m_Description;

		// Debug the positive and negative preferences of this activity
		for (Hint h : m_PositiveHints)
		{
			debug += "\n(+)" + h.m_Preference->GetPrintable();
		}
		for (Hint h : m_NegativeHints)
		{
			debug += "\n(-)" + h.m_Preference->GetPrintable();
		}

		return debug;
	}

	void LocationManager::AddLocation(std::shared_ptr<Location> location)
	{
		m_Locations.push_back(location);
	}

}
