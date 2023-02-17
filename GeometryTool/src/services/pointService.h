#pragma once

const char* pointsDB = "data/points.txt";

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

void getPoint(const std::string name, std::string& point)
{
	std::ifstream database(pointsDB);

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
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}
