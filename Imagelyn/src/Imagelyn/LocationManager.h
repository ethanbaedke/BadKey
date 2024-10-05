#pragma once
#include "imagelynpch.h"

#include "PreferenceManager.h"

namespace Imagelyn {

	class Activity : BadKey::IPrintable
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

		Activity(std::string name);

		std::vector<std::shared_ptr<Preference>> GetPositivePreferences();
		std::vector<std::shared_ptr<Preference>> GetNegativePreferences();

		/* Unlocks the hint on this activity for the input preference */
		void UnlockPositiveHint(std::shared_ptr<Preference> preference);
		void UnlockNegativeHint(std::shared_ptr<Preference> preference);

		/* Gets the unlocked hints to be displayed for this activity */
		std::vector<std::shared_ptr<Preference>> GetPositiveUnlockedHints();
		std::vector<std::shared_ptr<Preference>> GetNegativeUnlockedHints();

		inline void AddPositivePreference(std::shared_ptr<Preference> preference) { m_PositiveHints.push_back(Hint(preference)); }
		inline void AddNegativePreference(std::shared_ptr<Preference> preference) { m_NegativeHints.push_back(Hint(preference)); }
		inline const std::string& GetName() { return m_Name; }
		inline void SetDescription(std::string description) { m_Description = description; }

		virtual std::string GetPrintable() const;

	private:

		std::string m_Name;
		std::string m_Description;

		std::vector<Hint> m_PositiveHints;
		std::vector<Hint> m_NegativeHints;

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
