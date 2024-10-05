#pragma once
#include "imagelynpch.h"

namespace Imagelyn {

	class Preference : BadKey::IPrintable
	{

	public:

		Preference(std::string name);

		inline const std::string& GetName() { return m_Name; }

		virtual std::string GetPrintable() const;

	private:

		std::string m_Name;

	};

	class PreferenceManager
	{

	public:

		/* Adds a preference to the list, returns false if the input preference already exists in the list */
		static bool AddPreference(std::shared_ptr<Preference> preference);

		/* Returns the preference object with the input name if it exists in the list, nullptr otherwise */
		static std::shared_ptr<Preference> GetPreferenceByName(const std::string& preferenceName);

		/* Returns a random preference */
		static std::shared_ptr<Preference> GetRandomPreference();

	private:

		static std::vector<std::shared_ptr<Preference>> m_Preferences;

	};

}

