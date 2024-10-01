#include "Client.h"
#include "ConsoleManager.h"

#include <random>

namespace Imagelyn {

	Client::Client()
	{
		// Give the client a random name
		// THIS IS HORRIBLE!!! WHY DID I EVER WRITE THIS CODE?!?! Allow the user to input a name list to be loaded instead
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> nameDist(0, s_NamesCount - 1);
		int nameIndex = nameDist(gen);
		m_Name = s_Names[nameIndex];
	}

	std::string Client::GetName() const
	{
		return m_Name;
	}

	void Client::PrintClient() const
	{
		ConsoleManager::Log(m_Name, COLOR_DEFAULT);
		std::cout << std::endl;
	}

}