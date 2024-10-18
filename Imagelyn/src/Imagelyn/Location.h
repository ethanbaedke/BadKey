#pragma once
#include "imagelynpch.h"

#include "Preference.h"

namespace Imagelyn {

	class Activity
	{

	private:

		/* Container to hold preferences alongside a boolean for whether their hint is unlocked for this activity */
		struct Hint
		{
			std::shared_ptr<Preference> m_Preference;
			bool m_Unlocked;

			Hint(std::shared_ptr<Preference> preference)
				: m_Preference(preference), m_Unlocked(false)
			{
			}
		};

	public:

		Activity(const std::string name);

		const std::vector<std::shared_ptr<Preference>> GetPositivePreferences() const;
		const std::vector<std::shared_ptr<Preference>> GetNegativePreferences() const;

		/* Unlocks the hint on this activity for the input preference */
		void UnlockPositiveHint(std::shared_ptr<Preference> preference);
		void UnlockNegativeHint(std::shared_ptr<Preference> preference);

		/* Gets the unlocked hints to be displayed for this activity */
		const std::vector<std::shared_ptr<Preference>> GetPositiveUnlockedHints() const;
		const std::vector<std::shared_ptr<Preference>> GetNegativeUnlockedHints() const;

		inline void AddPositivePreference(std::shared_ptr<Preference> preference) { m_PositiveHints.push_back(Hint(preference)); }
		inline void AddNegativePreference(std::shared_ptr<Preference> preference) { m_NegativeHints.push_back(Hint(preference)); }
		inline const std::string& GetName() const { return m_Name; }

	private:

		/* Name of this activity */
		std::string m_Name;

		/* Preferences this activity is bound with contained in hints */
		std::vector<Hint> m_PositiveHints;
		std::vector<Hint> m_NegativeHints;

	};

	class Location
	{

	public:

		Location(std::string name);

		/* Add an activity to this location */
		void AddActivity(const std::shared_ptr<Activity> activity);

		inline const std::string& GetName() const { return m_Name; }
		inline const std::vector<std::shared_ptr<Activity>>& GetActivities() const { return m_Activities; }

	private:

		/* Name of this location */
		std::string m_Name;

		/* List of activities that can be selected from this location */
		std::vector<std::shared_ptr<Activity>> m_Activities;
	};

	class LocationManager
	{

	public:

		/* Adds a location to the game */
		static void AddLocation(std::shared_ptr<Location> location);

		static inline const std::vector<std::shared_ptr<Location>>& GetLocations() { return m_Locations; }

	private:

		/* List of all locations available in the game */
		static std::vector<std::shared_ptr<Location>> m_Locations;

	};

}
