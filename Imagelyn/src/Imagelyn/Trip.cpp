#include "imagelynpch.h"

#include "Trip.h"
#include "ConsoleManager.h"
#include "Menu.h"
#include "Report.h"

namespace Imagelyn {

	Stop::Stop(const std::string& name, std::shared_ptr<Location> location, Trip* trip)
		: m_Name(name), m_Location(location), m_AvailableActivities(location->GetActivities()), m_CurrentActivites(std::vector<std::shared_ptr<Activity>>()), m_OwningTrip(trip)
	{
	}

	void Stop::OpenStopMenu()
	{
		m_OwningTrip->GetClient().PrintClient();

		// Print all currently added activities
		for (const std::shared_ptr<Activity>& act : m_CurrentActivites)
		{
			ConsoleManager::Log(act->GetName(), COLOR_ACTIVITY);
		}

		ConsoleManager::BreakLine();

		Menu stopMenu(m_Name);

		if (m_AvailableActivities.size() > 0)
		{
			stopMenu.AddOption("Add Activity", COLOR_DEFAULT, [&]
				{
					// Create a menu listing all available activities that can be added to this stop
					Menu availableActivityMenu("Select an activity");
					for (int i = 0; i < m_AvailableActivities.size(); i++)
					{
						std::string optionString = m_AvailableActivities[i]->GetName();
						std::vector<std::shared_ptr<Preference>> posHints = m_AvailableActivities[i]->GetPositiveUnlockedHints();
						std::vector<std::shared_ptr<Preference>> negHints = m_AvailableActivities[i]->GetNegativeUnlockedHints();
						for (std::shared_ptr<Preference> pref : posHints)
							optionString += " (+" + pref->GetName() + ")";
						for (std::shared_ptr<Preference> pref : negHints)
							optionString += " (-" + pref->GetName() + ")";
						availableActivityMenu.AddOption(optionString, COLOR_ACTIVITY, [&, i]
							{
								m_CurrentActivites.push_back(m_AvailableActivities[i]);
								m_AvailableActivities.erase(m_AvailableActivities.begin() + i);
								OpenStopMenu();
							});
					}
					availableActivityMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
							m_OwningTrip->GetClient().PrintClient();
							stopMenu.Poll();
						});
					availableActivityMenu.Poll();
				});
		}

		if (m_CurrentActivites.size() > 0)
		{
			stopMenu.AddOption("Remove Activity", COLOR_DEFAULT, [&]
				{
					Menu currentActivityMenu("Select and activity to remove");
					for (int i = 0; i < m_CurrentActivites.size(); i++)
					{
						currentActivityMenu.AddOption(m_CurrentActivites[i]->GetName(), COLOR_ACTIVITY, [&, i]
							{
								m_AvailableActivities.push_back(m_CurrentActivites[i]);
								m_CurrentActivites.erase(m_CurrentActivites.begin() + i);
								OpenStopMenu();
							});
					}
					currentActivityMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
							m_OwningTrip->GetClient().PrintClient();
							stopMenu.Poll();
						});
					currentActivityMenu.Poll();
				});
		}

		stopMenu.AddOption("Back", COLOR_DEFAULT, [&]
			{
				m_OwningTrip->OpenPlanningMenu();
			});

		stopMenu.Poll();
	}

	Trip::Trip(const Client& client, std::vector<std::shared_ptr<Location>> availableLocations)
		: m_Client(client), m_AvailableLocations(availableLocations)
	{
	}

	void Trip::OpenPlanningMenu()
	{
		m_Client.PrintClient();

		Menu tripMenu("Plan Trip");

		if (m_Stops.size() > 0)
		{
			for (int i = 0; i < m_Stops.size(); i++)
			{
				tripMenu.AddOption("Edit Stop: " + m_Stops[i]->GetName(), COLOR_DEFAULT, [&, i]
					{
						m_Stops[i]->OpenStopMenu();
					});
			}
		}

		tripMenu.AddOption("Add Stop", COLOR_DEFAULT, [&]
			{
				// Create a menu to select a location
				Menu availableLocationMenu("Select a Destination");
				for (int i = 0; i < m_AvailableLocations.size(); i++)
				{
					availableLocationMenu.AddOption(m_AvailableLocations[i]->GetName(), COLOR_DEFAULT, [&, i]
						{
							// Create a new stop for the location
							std::shared_ptr<Stop> stop = std::make_shared<Stop>(m_AvailableLocations[i]->GetName(), m_AvailableLocations[i], this);
							m_Stops.push_back(stop);
							m_AvailableLocations.erase(m_AvailableLocations.begin() + i);
							stop->OpenStopMenu();
						});
				}
				availableLocationMenu.AddOption("Back", COLOR_DEFAULT, [&]
					{
						m_Client.PrintClient();
						tripMenu.Poll();
					});
				availableLocationMenu.Poll();
			});

		if (m_Stops.size() > 0)
		{
			tripMenu.AddOption("Remove Stop", COLOR_DEFAULT, [&]
				{
					Menu currentLocationMenu("Select a Destination");
					for (int i = 0; i < m_Stops.size(); i++)
					{
						currentLocationMenu.AddOption(m_Stops[i]->GetLocation()->GetName(), COLOR_DEFAULT, [&, i]
							{
								// Remove the stop from the list and re-add the location as an available location
								m_AvailableLocations.push_back(m_Stops[i]->GetLocation());
								m_Stops.erase(m_Stops.begin() + i);
								OpenPlanningMenu();
							});
					}
					currentLocationMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
							m_Client.PrintClient();
							tripMenu.Poll();
						});
					currentLocationMenu.Poll();
				});
		}

		tripMenu.AddOption("Finalize Trip", COLOR_DEFAULT, [&]
			{
				std::vector<std::shared_ptr<Activity>> activities;
				for (std::shared_ptr<Stop> stop : m_Stops)
				{
					for (std::shared_ptr<Activity> activity : stop->GetCurrentActivities())
					{
						activities.push_back(activity);
					}
				}
				std::shared_ptr<Report> rep = ReportManager::GenerateReport(m_Client, activities);
				rep->PrintReport();
			});

		tripMenu.Poll();
	}

}