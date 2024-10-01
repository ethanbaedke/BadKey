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

	std::string Activity::GetPrintable() const
	{
		// Debug the name of this activity
		std::string debug = "Activity: " + m_Name;
		
		// Debug the description of this activity
		debug += "\n" + std::string("Description: ") + m_Description;

		// Debug the positive and negative preferences of this activity
		for (std::shared_ptr<Preference> p : m_PositivePreferences)
		{
			debug += "\n(+)" + p->GetPrintable();
		}
		for (std::shared_ptr<Preference> p : m_NegativePreferences)
		{
			debug += "\n(-)" + p->GetPrintable();
		}

		return debug;
	}

	void LocationManager::AddLocation(std::shared_ptr<Location> location)
	{
		m_Locations.push_back(location);
	}

}
