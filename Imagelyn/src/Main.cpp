#include <BadKey.h>
#include <filesystem>

#include "FileInterpreter.h"
#include "Menu.h"
#include "ConsoleManager.h"
#include "Client.h"
#include "Trip.h"

namespace Imagelyn {

	class ImagelynApplication : public BadKey::Application
	{

	public:

		ImagelynApplication()
		{
			LoadData();

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

	private:

		/* Load all important files and populate objects with their data */
		void LoadData()
		{
			// Load preference data
			FileInterpreter::Load("data/PreferenceInit.txt");

			// Load location data
			for (const std::filesystem::directory_entry& file : std::filesystem::directory_iterator("data"))
			{
				if (file.is_regular_file() && file.path().extension() == ".txt" && file.path().filename().string() != "PreferenceInit.txt")
				{
					FileInterpreter::Load("data/" + file.path().filename().string());
				}
			}
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