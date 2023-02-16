#pragma once

void saveLine(const std::string name, const double k, double n)
{
	std::string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	std::ofstream dataBase(linesDB, std::fstream::app);

	if (dataBase.is_open())
	{
		std::string data = name + " : " + toString(k) + "*x" + symbol + toString(n);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void savePoint(const std::string name, const double x, const double y)
{
	std::ofstream  dataBase(pointsDB, std::ios::app);

	if (dataBase.is_open())
	{
		std::string data = name + " : " + toString(x) + ";" + toString(y);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

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

void deleteLine(const std::string name)
{
	std::string rowText;

	std::ifstream dataBase(linesDB);
	std::ofstream  newDataBase("linesNew.txt");

	if (dataBase.is_open() && newDataBase.is_open())
	{
		while (std::getline(dataBase, rowText))
		{
			std::vector<std::string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				continue;
			}

			newDataBase << rowText << "\n";
		}

		dataBase.close();
		newDataBase.close();

		remove(linesDB);
		if (rename("linesNew.txt", linesDB))
		{
			stopProgram = true;
			std::cerr << "There was an error with the deleting of the line!\nWe are sorry. . .\n";
		}
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
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

void deletePoint(const std::string name)
{
	std::string rowText;

	std::ifstream dataBase(pointsDB);
	std::ofstream  newDataBase("pointsNew.txt");

	if (dataBase.is_open() && newDataBase.is_open())
	{
		while (std::getline(dataBase, rowText))
		{
			std::vector<std::string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				continue;
			}

			newDataBase << rowText << "\n";
		}

		dataBase.close();
		newDataBase.close();

		remove(pointsDB);
		if (rename("pointsNew.txt", pointsDB) != 0)
		{
			stopProgram = true;
			std::cerr << "There was an error with the deleting of the point!\nWe are sorry. . .\n";
		}
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
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
