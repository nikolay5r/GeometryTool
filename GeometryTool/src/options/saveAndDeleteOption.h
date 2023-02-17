#pragma once

void savePointOption(std::string name = "")
{
	double x = 0,
		y = 0;

	if (name == "")
	{
		std::cout << ENTER_NAME_TEXT;
		std::getline(std::cin, name);
	}

	if (!isNameValid(name))
	{
		savePointOption();
	}
	else if (isElementInDatabase(name, pointsDB))
	{
		std::cerr << NAME_EXISTS_TEXT;
		savePointOption();
	}
	else
	{
		setPointCoordinates(x, y);
		savePoint(name, x, y);
	}
}

void saveLineOption(std::string name = "")
{
	double k, n;

	if (name == "")
	{
		std::cout << ENTER_NAME_TEXT;
		std::getline(std::cin, name);
	}

	if (!isNameValid(name))
	{
		saveLineOption();
	}
	else if (isElementInDatabase(name, linesDB))
	{
		std::cerr << NAME_EXISTS_TEXT;
		saveLineOption();
	}
	else
	{
		setEquationOfLine(k, n);
		saveLine(name, k, n);
	}
}

void saveOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		saveLineOption();
		saveAnimation();
	}
	else if (keyword == "point")
	{
		savePointOption();
		saveAnimation();
	}
	else if (keyword != "menu")
	{
		std::cerr << INVALID_INPUT_TEXT;
		saveOption();
	}
}

void deleteLineOption()
{
	std::string name;

	std::cout << "Enter the name of the line: ";
	std::getline(std::cin, name);

	if (!isElementInDatabase(name, linesDB))
	{
		std::cerr << NAME_DOESNT_EXIST_TEXT;
		deleteLineOption();
	}
	else
	{
		deleteLine(name);
	}
}

void deletePointOption()
{
	std::string name;

	std::cout << "Enter the name of the point: ";
	std::getline(std::cin, name);

	if (!isElementInDatabase(name, pointsDB))
	{
		std::cerr << NAME_DOESNT_EXIST_TEXT;
		deletePointOption();
	}
	else
	{
		deletePoint(name);
	}
}

void deleteOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		deleteLineOption();
		deleteAnimation();
	}
	else if (keyword == "point")
	{
		deletePointOption();
		deleteAnimation();
	}
	else if (keyword != "menu")
	{
		std::cerr << INVALID_INPUT_TEXT;
	}
}

void saveOrDeleteOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "save")
	{
		std::cout << "Enter \"line\" if you want to save a line\n"
			<< "Enter \"point\" if you want to save a point\n"
			<< GO_TO_MAIN_MENU_TEXT;

		saveOption();
	}
	else if (keyword == "delete")
	{
		std::cout << "Enter \"line\" if you want to delete a line\n"
			<< "Enter \"point\" if you want to delete a point\n"
			<< GO_TO_MAIN_MENU_TEXT;

		deleteOption();
	}
	else if (keyword != "menu")
	{
		std::cerr << INVALID_INPUT_TEXT;
		saveOrDeleteOption();
	}
}
