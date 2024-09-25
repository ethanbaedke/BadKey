#include <BadKey.h>

class ImagelynApplication : public BadKey::Application
{

public:

	ImagelynApplication()
	{
		BadKey::MouseClickEvent e(0, BadKey::ButtonInteraction::ButtonDown);
		BK_MESSAGE(e.GetPrintable());
	}

};

int main()
{
	ImagelynApplication* app = new ImagelynApplication();
	app->Run();
	delete app;

	return 0;
}