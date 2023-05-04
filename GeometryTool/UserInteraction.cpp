#include <iostream>
#include <string>

#include "Validation.h"
#include "Constants.h"
#include "Helper.h"
#include "Animation.h"
#include "LineService.h"
#include "PointService.h"

void getN(double& n)
{
	std::string stringN;
	std::cout << "Enter n: ";
	std::getline(std::cin, stringN);
	if (!isInputNumber(stringN))
	{
		getN(n);
	}
	else
	{
		n = stod(stringN);
		if (!isNumberValid(n))
		{
			getN(n);
		}
	}
}

void getSlope(double& k)
{
	std::string stringK;
	std::cout << "Enter slope (k): ";
	std::getline(std::cin, stringK);
	if (!isInputNumber(stringK))
	{
		getSlope(k);
	}
	else
	{
		k = stod(stringK);
		if (!isNumberValid(k))
		{
			getSlope(k);
		}
	}
}

std::string getKeywordFromConsole()
{
	std::cout << "Keyword: ";

	std::string keyword = "";

	std::getline(std::cin, keyword);

	std::cout << "\n";

	convertToLowerCase(keyword);

	return keyword;
}

void getXCoord(double& x)
{
	std::string stringX;
	std::cout << "x: ";
	std::getline(std::cin, stringX);

	if (!isInputNumber(stringX))
	{
		getXCoord(x);
	}
	else
	{
		x = stod(stringX);
		if (!isNumberValid(x))
		{
			getXCoord(x);
		}
	}
}

void getYCoord(double& y)
{
	std::string Y;
	std::cout << "y: ";
	std::getline(std::cin, Y);

	if (!isInputNumber(Y))
	{
		getYCoord(y);
	}
	else
	{
		y = stod(Y);
		if (!isNumberValid(y))
		{
			getYCoord(y);
		}
	}
}

void setEquationOfLine(double& k, double& n)
{
	std::cout << "Enter the equation of the line using this format \"k*x + n\"\n";
	getSlope(k);
	getN(n);
}

void setPointCoordinates(double& x, double& y)
{
	std::string stringX,
		Y;

	std::cout << "Enter coordinates:\n";

	getXCoord(x);
	getYCoord(y);
}

void getAnswer(std::string& answer, std::string question)
{
	std::cout << question;
	std::getline(std::cin, answer);
	convertToLowerCase(answer);

	if (answer != "no" && answer != "yes")
	{
		std::cerr << constants::INVALID_INPUT_TEXT;
		getAnswer(answer, question);
	}
}

void getName(std::string& name)
{
	std::cout << constants::ENTER_NAME_TEXT;
	std::getline(std::cin, name);
	if (!isNameValid(name))
	{
		getName(name);
	}
}

void wantToSaveLine(const double k, const double n, std::string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to save the line? ");
	}

	if (answer == "yes")
	{
		std::string name;
		getName(name);

		if (isElementInDatabase(name, constants::linesDB))
		{
			std::cout << constants::NAME_EXISTS_TEXT;
			wantToSaveLine(k, n, answer);
		}
		else
		{
			saveAnimation();
			saveLine(name, k, n);
		}
	}
}

void wantToSavePoint(const double x, const double y, std::string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to save the point? ");
	}

	if (answer == "yes")
	{
		std::string name;
		getName(name);

		if (isElementInDatabase(name, constants::pointsDB))
		{
			std::cerr << constants::NAME_EXISTS_TEXT;
			wantToSavePoint(x, y, answer);
		}
		else
		{
			savePoint(name, x, y);
			saveAnimation();
		}
	}
}

void wantToUseExistingPoint(std::string& point, std::string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to use existing point? ");
	}

	if (answer == "yes")
	{
		std::string name;
		getName(name);

		if (isElementInDatabase(name, constants::pointsDB))
		{
			loadAnimation();
			getPoint(name, point);
		}
		else
		{
			std::cerr << constants::NAME_DOESNT_EXIST_TEXT;
			wantToUseExistingPoint(point, answer);
		}
	}
}

void wantToUseExistingLine(std::string& line, std::string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to use existing line? ");
	}

	if (answer == "yes")
	{
		std::string name;
		getName(name);

		if (isElementInDatabase(name, constants::linesDB))
		{
			loadAnimation();
			getEquationOfLine(name, line);
		}
		else
		{
			std::cerr << constants::NAME_DOESNT_EXIST_TEXT;
			wantToUseExistingLine(line, answer);
		}
	}
}

void getCoordinatesFromExistingPoint(std::string point, double& x, double& y)
{
	std::vector<std::string> coordinates;
	splitByDelim(coordinates, point, ";");

	x = stod(coordinates[0]);
	y = stod(coordinates[1]);
}

void getArgumentsFromExistingLine(std::string equation, double& k, double& n)
{
	std::vector<std::string> arguments;
	splitByDelim(arguments, equation, "*x");

	k = stod(arguments[0]);
	n = stod(arguments[1]);
}

void getLineArguments(double& k, double& n)
{
	std::string line = "";

	wantToUseExistingLine(line);

	if (line == "")
	{
		setEquationOfLine(k, n);
		wantToSaveLine(k, n);
	}
	else
	{
		getArgumentsFromExistingLine(line, k, n);
	}
}

void getPointCoordinates(double& x, double& y)
{
	std::string point = "";
	wantToUseExistingPoint(point);

	if (point == "")
	{
		setPointCoordinates(x, y);
		wantToSavePoint(x, y);
	}
	else
	{
		getCoordinatesFromExistingPoint(point, x, y);
	}
}

void getParabola(double& p)
{
	std::cout << "Enter a parabola in this format \"y^2 = 2px\":\n";
	std::cout << "p: ";
	std::cin >> p;
	if (!isNumberValid(p))
	{
		std::cerr << "P-argument is too large! It should be between -100 and 100!\n";
	}
}
