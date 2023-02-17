#pragma once

bool isInputNumber(std::string input)
{
	int counterDots = 0;
	int index = 0;

	if (input[0] == '-')
	{
		index++;
	}

	for (; index < input.length(); index++)
	{
		char currentChar = input[index];
		if (currentChar == '.' || currentChar == ',')
		{
			counterDots++;
		}

		if (counterDots > 1 || (currentChar < '0' || currentChar > '9'))
		{
			std::cerr << INVALID_INPUT_TEXT;
			return false;
		}
	}

	return true;
}

bool isNumberValid(const double number)
{
	if (abs(number) <= maxNumberSize)
	{
		return true;
	}
	std::cerr << INVALID_NUMBER_TEXT;
	return false;
}

bool areLinesTheSame(double k1, double n1, double k2, double n2)
{
	return k1 == k2 && n1 == n2;
}

bool isNameValid(const std::string name)
{
	if (name.length() > maxLengthOfName)
	{
		std::cerr << "The name is too long! Try again...\n";
		return false;
	}

	for (int i = 0; i < name.length(); i++)
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= '0' && name[i] <= '9')
			|| name[i] == '_'))
		{
			std::cerr << "Invalid characters in name! Try again...\n";
			return false;
		}
	}

	return true;
}

bool arePointsTheSame(double& x1, double& y1, double& x2, double& y2)
{
	return (x1 == x2 && y1 == y2);
}

bool arePointsOnTheSameLine(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double k, n;

	calculateLineByTwoPoints(k, n, x1, y1, x2, y2);

	return (y3 == k * x3 + n);
}

bool checkIfTetragonCanBeCreated(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4)
{
	if ((areLinesTheSame(k1, n1, k2, n2) || areLinesTheSame(k1, n1, k3, n3)) ||
		(areLinesTheSame(k1, n1, k4, n4) || areLinesTheSame(k3, n3, k2, n2)) ||
		(areLinesTheSame(k4, n4, k2, n2) || areLinesTheSame(k3, n3, k4, n4)))
	{
		std::cerr << "You used the same line at least twice! Cannot create a tetragon!\n";
		return false;
	}

	if ((((k1 == k2) && (k2 == k3)) || ((k1 == k2) && (k2 == k4))) ||
		(((k1 == k3) && (k3 == k4)) || (k2 == k3) && (k3 == k4)))
	{
		std::cerr << "Cannot create a tetragon! At least three of the lines are parallel!\n";
		return false;
	}

	return true;
}
bool areLinesPerpendicular(double k1, double k2)
{
	return (k1 == (-1 / k2));
}

bool isTetragonRectangle(double k1, double k2, double k3, double k4)
{
	return (areLinesPerpendicular(k1, k2) && areLinesPerpendicular(k1, k3) && k1 == k4) ||
		(areLinesPerpendicular(k1, k2) && areLinesPerpendicular(k1, k4) && k1 == k3) ||
		(areLinesPerpendicular(k1, k3) && areLinesPerpendicular(k1, k4) && k1 == k2);
}

bool areAllSidesEqual(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4)
{
	double xa, ya,
		xb, yb,
		xc, yc,
		xd, yd;

	calculateIntersectionPointOfTwoLines(xa, ya, k1, n1, k4, n4);
	calculateIntersectionPointOfTwoLines(xb, yb, k1, n1, k2, n2);
	calculateIntersectionPointOfTwoLines(xc, yc, k2, n2, k3, n3);
	calculateIntersectionPointOfTwoLines(xd, yd, k3, n3, k4, n4);


	double AB = sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
	double AD = sqrt((xd - xa) * (xd - xa) + (yd - ya) * (yd - ya));
	double BC = sqrt((xc - xb) * (xc - xb) + (yc - yb) * (yc - yb));
	double CD = sqrt((xd - xc) * (xd - xc) + (yd - yc) * (yd - yc));

	return (AB == AD && AD == BC && BC == CD);
}

bool isElementInDatabase(const std::string element, const char* path)
{
	std::ifstream dataBase(path);

	if (dataBase.is_open())
	{
		std::string rowText;

		while (std::getline(dataBase, rowText))
		{
			std::vector<std::string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == element)
			{
				dataBase.close();
				return true;
			}
		}
	}
	else
	{
		std::cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}

	dataBase.close();
	return false;
}
