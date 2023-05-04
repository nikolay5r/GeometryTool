#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "Constants.h"
#include "Helper.h"

void saveLine(const std::string name, const double k, double n)
{
	std::string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	std::ofstream dataBase(constants::linesDB, std::ios::app);

	if (dataBase.is_open())
	{
		std::string data = name + " : " + toString(k) + "*x" + symbol + toString(n);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		std::cerr << constants::DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void getEquationOfLine(const std::string name, std::string& equation)
{
	std::ifstream database(constants::linesDB);

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
		std::cerr << constants::DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void deleteLine(const std::string name)
{
	std::string rowText;

	std::ifstream dataBase(constants::linesDB);
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

		remove(constants::linesDB);
		if (rename("linesNew.txt", constants::linesDB))
		{
			std::cerr << "There was an error with the deleting of the line!\nWe are sorry. . .\n";
			throw std::runtime_error("ERROR with renaming the file on deleting line!");
		}
	}
	else
	{
		std::cerr << constants::DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}
