#pragma once

#include <BadKey.h>

namespace Imagelyn {

	class Menu
	{

	private:

		struct MenuOption
		{
			std::string optionText;
			const char* optionColor;
			std::function<void()> optionFunction;
		};

	private:

		/* The name of the menu, which will be displayed alongside it */
		std::string m_Title;

		/* List of options that can be chosen from this menu */
		std::vector<MenuOption> m_Options;

	public:

		Menu(const std::string& title);

		/* Add a new option to this menu */
		void AddOption(const std::string& text, const char* color, std::function<void()> func);

		/* Print all options in this menu to the console and waits for the user to choose one */
		void Poll() const;

	private:

		/* Select an option from this menu */
		void Select(int index) const;

	};

}

