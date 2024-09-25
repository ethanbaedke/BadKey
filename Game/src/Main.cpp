#include "BadKey.h"

class GameApplication : public BadKey::Application
{

public:

	GameApplication()
	{
		BK_MESSAGE("Hello World!");
	}

};

int main()
{
	GameApplication* game = new GameApplication();
	game->Run();
	delete game;

	return 0;
}