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

void getEquationOfLine(const std::string name, std::string& equation)
{
	std::ifstream database(linesDB);

	if (database.is_open())
	{
		std::string rowText;

		while (std::getline(database, rowText))
		{
			std::vector<std::string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				equation = words[1];
				break;
			}
		}

		database.close();
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
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
