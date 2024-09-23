#include <BadKey.h>

class ImagelynApplication : public BadKey::Application
{

};

int main()
{
	ImagelynApplication* app = new ImagelynApplication();
	app->Run();
	delete app;

	return 0;
}