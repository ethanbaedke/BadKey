#include "BadKey.h"

class ImagelynApplication : public BadKey::Application
{

public:

	ImagelynApplication()
	{
		BK_MESSAGE("Hello World!");
	}

};

int main()
{
	ImagelynApplication* app = new ImagelynApplication();
	app->Run();
	delete app;

	return 0;
}