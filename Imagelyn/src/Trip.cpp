#include "Trip.h"
#include "ConsoleManager.h"
#include "LocationManager.h"

namespace Imagelyn {

	Stop::Stop(const std::string& name, std::shared_ptr<Location> location, Trip* trip)
		: m_Name(name), m_Location(location), m_AvailableActivities(location->GetActivities()), m_CurrentActivites(std::vector<std::shared_ptr<Activity>>()), m_OwningTrip(trip)
	{
	}

	void Stop::OpenStopMenu()
	{
		Menu stopMenu(m_Name);

		if (m_CurrentActivites.size() > 0)
		{
			stopMenu.AddOption("View Itinerary", COLOR_DEFAULT, [&]
				{
					// Print all currently added activities
					for (std::shared_ptr<Activity>& act : m_CurrentActivites)
					{
						ConsoleManager::Log(act->GetName(), COLOR_DEFAULT);
					}
					OpenStopMenu();
				});
		}

		if (m_AvailableActivities.size() > 0)
		{
			stopMenu.AddOption("Add Activity", COLOR_DEFAULT, [&]
				{
					// Create a menu listing all available activities that can be added to this stop
					Menu availableActivityMenu("Select an activity");
					for (int i = 0; i < m_AvailableActivities.size(); i++)
					{
						availableActivityMenu.AddOption(m_AvailableActivities[i]->GetName(), COLOR_DEFAULT, [&, i]
							{
								m_CurrentActivites.push_back(m_AvailableActivities[i]);
								m_AvailableActivities.erase(m_AvailableActivities.begin() + i);
								OpenStopMenu();
							});
					}
					availableActivityMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
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
						currentActivityMenu.AddOption(m_CurrentActivites[i]->GetName(), COLOR_DEFAULT, [&, i]
							{
								m_AvailableActivities.push_back(m_CurrentActivites[i]);
								m_CurrentActivites.erase(m_CurrentActivites.begin() + i);
								OpenStopMenu();
							});
					}
					currentActivityMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
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
		Menu tripMenu("Plan Trip");

		tripMenu.AddOption("View Client Details", COLOR_DEFAULT, [&]
			{
				m_Client.PrintClient();
				tripMenu.Poll();
			});

		if (m_Stops.size() > 0)
		{
			for (int i = 0; i < m_Stops.size(); i++)
			{
				tripMenu.AddOption("Edit Stop: " + m_Stops[i].GetName(), COLOR_DEFAULT, [&, i]
					{
						m_Stops[i].OpenStopMenu();
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
							Stop stop(m_AvailableLocations[i]->GetName(), m_AvailableLocations[i], this);
							m_Stops.push_back(stop);
							m_AvailableLocations.erase(m_AvailableLocations.begin() + i);
							stop.OpenStopMenu();
						});
				}
				availableLocationMenu.AddOption("Back", COLOR_DEFAULT, [&]
					{
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
						currentLocationMenu.AddOption(m_Stops[i].GetLocation()->GetName(), COLOR_DEFAULT, [&, i]
							{
								// Remove the stop from the list and re-add the location as an available location
								m_AvailableLocations.push_back(m_Stops[i].GetLocation());
								m_Stops.erase(m_Stops.begin() + i);
								OpenPlanningMenu();
							});
					}
					currentLocationMenu.AddOption("Back", COLOR_DEFAULT, [&]
						{
							tripMenu.Poll();
						});
					currentLocationMenu.Poll();
				});
		}

		tripMenu.Poll();
	}

}