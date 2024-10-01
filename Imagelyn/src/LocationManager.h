#pragma once

#include "PreferenceManager.h"

#include <BadKey.h>
#include <vector>
#include <memory>

namespace Imagelyn {

	class Activity : BadKey::IPrintable
	{

	public:

		Activity(std::string name);

		inline void AddPositivePreference(std::shared_ptr<Preference> preference) { m_PositivePreferences.push_back(preference); }
		inline void AddNegativePreference(std::shared_ptr<Preference> preference) { m_NegativePreferences.push_back(preference); }
		inline std::string& GetName() { return m_Name; }
		inline void SetDescription(std::string description) { m_Description = description; }

		virtual std::string GetPrintable() const;

	private:

		std::string m_Name;
		std::string m_Description;

		std::vector<std::shared_ptr<Preference>> m_PositivePreferences;
		std::vector<std::shared_ptr<Preference>> m_NegativePreferences;

	};

	class Location : BadKey::IPrintable
	{

	public:

		Location(std::string name);

		void AddActivity(const std::shared_ptr<Activity> activity);

		inline std::string& GetName() { return m_Name; }
		inline std::vector<std::shared_ptr<Activity>>& GetActivities() { return m_Activities; }

		virtual std::string GetPrintable() const;

	private:

		std::string m_Name;

		std::vector<std::shared_ptr<Activity>> m_Activities;
	};

	class LocationManager
	{

	public:

		static void AddLocation(std::shared_ptr<Location> location);

		static inline const std::vector<std::shared_ptr<Location>>& GetLocations() { return m_Locations; }

	private:

		static std::vector<std::shared_ptr<Location>> m_Locations;

	};

}
