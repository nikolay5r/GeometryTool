#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Constants.h"
#include "Helper.h"
#include "Validation.h"

void savePoint(const std::string name, const double x, const double y)
{
	std::ofstream  dataBase(constants::pointsDB, std::ios::app);

	if (dataBase.is_open())
	{
		std::string data = name + " : " + toString(x) + ";" + toString(y);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		std::cerr << constants::DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void deletePoint(const std::string name)
{
	std::string rowText;

	std::ifstream dataBase(constants::pointsDB);
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

		remove(constants::pointsDB);
		if (rename("pointsNew.txt", constants::pointsDB) != 0)
		{
			std::cerr << "There was an error with the deleting of the point!\nWe are sorry. . .\n";
			throw std::runtime_error("ERROR with renaming the file on deleting point!");
		}
	}
	else
	{
		std::cerr << constants::DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void getPoint(const std::string name, std::string& point)
{
	std::ifstream database(constants::pointsDB);

	if (database.is_open())
	{
		std::string rowText;

		while (std::getline(database, rowText))
		{
			std::vector<std::string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				point = words[1];
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
