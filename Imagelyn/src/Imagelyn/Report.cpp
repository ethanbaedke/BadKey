#include "imagelynpch.h"

#include "Report.h"
#include "ConsoleManager.h"

namespace Imagelyn {

	std::vector<std::shared_ptr<Report>> ReportManager::m_Reports;

	Report::Report(const Client& client, const std::vector<std::shared_ptr<Activity>>& activities)
		: m_Score(0), m_Pairings(std::vector<Pairing>())
	{
		std::vector<std::shared_ptr<Preference>> clientPrefs = client.GetPreferences();
		// Go through all client preferences
		for (int clientPrefIndex = 0; clientPrefIndex < clientPrefs.size(); clientPrefIndex++)
		{
			// Go through all activities
			for (int activityIndex = 0; activityIndex < activities.size(); activityIndex++)
			{
				// Go through all positive preferences
				std::vector<std::shared_ptr<Preference>> posPrefs = activities[activityIndex]->GetPositivePreferences();
				for (int i = 0; i < posPrefs.size(); i++)
				{
					if (posPrefs[i] == clientPrefs[clientPrefIndex])
					{
						Pairing p(activities[activityIndex], posPrefs[i], true);
						m_Pairings.push_back(p);
						m_Score++;
					}
				}

				// Go through all negative preferences
				std::vector<std::shared_ptr<Preference>> negPrefs = activities[activityIndex]->GetNegativePreferences();
				for (int i = 0; i < negPrefs.size(); i++)
				{
					if (negPrefs[i] == clientPrefs[clientPrefIndex])
					{
						Pairing p(activities[activityIndex], negPrefs[i], false);
						m_Pairings.push_back(p);
						m_Score--;
					}
				}
			}
		}
	}

	void Report::PrintReport() const
	{
		for (const Pairing& p : m_Pairings)
		{
			auto color = p.m_IsPositive ? COLOR_POSITIVE : COLOR_NEGATIVE;
			ConsoleManager::Log(p.m_Activity->GetName() + " - " + p.m_Preference->GetName(), color);
		}
		ConsoleManager::BreakLine();
		ConsoleManager::Log("Score: " + std::to_string(m_Score), COLOR_DEFAULT);
	}

	const std::shared_ptr<Report>& ReportManager::GenerateReport(const Client& client, const std::vector<std::shared_ptr<Activity>>& activities)
	{
		std::shared_ptr<Report> rep = std::make_shared<Report>(client, activities);
		m_Reports.push_back(rep);
		return rep;
	}

}