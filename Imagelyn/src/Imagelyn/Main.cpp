#include "imagelynpch.h"

#include "ConsoleManager.h"
#include "Client.h"
#include "Menu.h"
#include "Trip.h"
#include "FileInterpreter.h"

#include <filesystem>

namespace Imagelyn {

	class ImagelynApplication : public BadKey::Application
	{

	public:

		ImagelynApplication()
		{
			if (!LoadData())
				return;

			if (!PreferenceManager::ValidPreferenceInit())
				return;

			while (true)
			{
				ConsoleManager::BreakLine();

				// Generate 3 potential clients
				Client potentialClients[3];

				// Create client selection menu
				Menu clientSelectMenu = Menu("Select a client");
				for (int i = 0; i < 3; i++)
				{
					clientSelectMenu.AddOption(potentialClients[i].GetName(), COLOR_DEFAULT, [&, i]
						{
							// Show client information
							potentialClients[i].PrintClient();

							// Create menu for confirming client selection
							Menu clientConfirmMenu = Menu(std::string("Confirm ") + potentialClients[i].GetName() + " as your client?");
							clientConfirmMenu.AddOption("Yes", COLOR_DEFAULT, [&, i]
								{
									Trip trip(potentialClients[i], LocationManager::GetLocations());
									trip.OpenPlanningMenu();
								});
							clientConfirmMenu.AddOption("No", COLOR_DEFAULT, [&]
								{
									clientSelectMenu.Poll();
								});
							clientConfirmMenu.Poll();
						});
				}
				clientSelectMenu.Poll();
			}
		}

	private:

		/* Load all important files and populate objects with their data */
		bool LoadData()
		{
			// Load preference data
			if (!FileInterpreter::Load("data/PreferenceInit.txt"))
				return false;

			// Load location data
			for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator("data"))
			{
				if (file.is_regular_file() && file.path().extension() == ".txt" && file.path().filename().string() != "PreferenceInit.txt")
				{
					if (FileInterpreter::Load("data/" + file.path().filename().string()))
						return false;
				}
			}
			return true;
		}

	};

}

int main()
{
	Imagelyn::ImagelynApplication* app = new Imagelyn::ImagelynApplication();
	app->Run();
	delete app;

	return 0;
}