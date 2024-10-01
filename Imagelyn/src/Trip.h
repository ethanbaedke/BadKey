#pragma once

#include "Client.h"
#include "LocationManager.h"
#include "Menu.h"

#include <memory>

namespace Imagelyn {

	class Trip;

	class Stop
	{

	private:

		/* The name of the stop */
		std::string m_Name;

		/* The location this stop is at */
		std::shared_ptr<Location> m_Location;

		/* List of all available activities at this stop, exclusing activites already selected for this stop */
		std::vector<std::shared_ptr<Activity>> m_AvailableActivities;

		/* List of chosen activities for this stop */
		std::vector<std::shared_ptr<Activity>> m_CurrentActivites;

		/* The trip that this stop is a part of */
		Trip* m_OwningTrip;

	public:

		Stop(const std::string& name, std::shared_ptr<Location> location, Trip* trip);

		inline std::string& GetName() { return m_Name; }
		inline std::shared_ptr<Location> GetLocation() { return m_Location; }

		/* Creates and opens a menu for adding/removing days from this stop */
		void OpenStopMenu();

	};

	class Trip
	{

	private:

		/* The client that this trip is for */
		Client m_Client;

		/* List of all available locations for this trip, exclusing locations already selected for this trip */
		std::vector<std::shared_ptr<Location>> m_AvailableLocations;

		/* A list of all stops on the trip */
		std::vector<Stop> m_Stops;

	public:

		Trip(const Client& client, std::vector<std::shared_ptr<Location>> availableLocations);

		/* Creates and opens a menu for displaying client info, adding/removing destinations, and finalizing the trip */
		void OpenPlanningMenu();

	};

}
