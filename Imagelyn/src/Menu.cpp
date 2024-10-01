#include "Menu.h"
#include "ConsoleManager.h"

namespace Imagelyn {

	Menu::Menu(const std::string& title)
		: m_Title(title), m_Options(std::vector<MenuOption>())
	{
	}

	void Menu::AddOption(const std::string& text, const char* color, std::function<void()> func)
	{
		// Create the new option
		MenuOption newOption;
		newOption.optionText = text;
		newOption.optionColor = color;
		newOption.optionFunction = func;

		// Add it to the list
		m_Options.push_back(newOption);
	}

	void Menu::Poll() const
	{
		ConsoleManager::Log(m_Title, COLOR_DEFAULT);

		// Display the option number and text of each option
		for (int i = 0; i < m_Options.size(); i++)
		{
			ConsoleManager::Log(std::to_string(i + 1) + ": " + m_Options[i].optionText, m_Options[i].optionColor);
		}

		std::cout << std::endl;

		int selection = ConsoleManager::GetInt(1, m_Options.size(), "Input", COLOR_DEFAULT);

		// Select option
		Select(selection);
	}

	void Menu::Select(int index) const
	{
		index--;
		if (index < m_Options.size() && index >= 0)
		{
			// Call the function on the selected option
			m_Options[index].optionFunction();
		}
		else
		{
			BK_WARNING("The choosen selection does not exist in the menu");
		}
	}

}