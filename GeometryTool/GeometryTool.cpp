
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <string.h>
#include <string>
#include <windows.h>

#include "Animation.h"
#include "Helper.h"
#include "Validation.h"

const int timeToWait = 1200;
const int maxLengthOfName = 16;
const int maxNumberSize = 100;

const char* linesDB = "lines.txt";
const char* pointsDB = "points.txt";

const char* SAVE_OR_DELETE_CORRESPONDING_NUMBER = "0";
const char* DEFINE_LINE_CORRESPONDING_NUMBER = "1";
const char* CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER = "2";
const char* FIND_PARALEL_LINE_CORRESPONDING_NUMBER = "3";
const char* FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER = "4";
const char* FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER = "5";
const char* FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER = "6";
const char* FIND_THE_TANGENT_CORRESPONDING_NUMBER = "7";
const char* DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER = "8";

const char* INVALID_INPUT_TEXT = "Invalid input! Try again...\n";
const char* GO_TO_MAIN_MENU_TEXT = "Enter the word \"menu\" if you want to go to the main menu\n";
const char* DATABASE_CANNOT_OPEN_TEXT = "ERROR! We are sorry the database cannot be opened!\n";
const char* ENTER_NAME_TEXT = "Enter name (it can be upper and lower case letters, \'_\' and numbers and 16 characters long): \n";
const char* NAME_EXISTS_TEXT = "Name already exists! Try another. . .\n";
const char* NAME_DOESNT_EXIST_TEXT = "Name doesn't exist! Try another. . .\n";
const char* INVALID_NUMBER_TEXT = "Number is too large! It should be between -100 and 100!\n";

bool stopProgram = false;

void printLine(const double k, double n, const double x1, const double y1, const double x2 = 102, const double y2 = 102)
{
	std::string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	std::cout << "The equation of the line is: ";

	if (x1 == x2)
	{
		std::cout << "x = " << x1;
	}
	else if (y1 == y2)
	{
		std::cout << "y = " << y1;
	}
	else if (k != 1 && k != 0)
	{
		if (n == 0)
		{
			std::cout << "y = " << k << " * x";
		}
		else
		{
			std::cout << "y = " << k << " * x " << symbol << " " << n;
		}
	}
	else if (k == 1)
	{
		std::cout << "y = x " << symbol << " " << n;
	}
	else
	{
		if (symbol == "+")
		{
			std::cout << "y = " << n;
		}
		else
		{
			std::cout << "y = " << symbol << n;
		}
	}

	std::cout << "\n";
}

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

std::string toString(double number)
{
	std::stringstream ss;
	ss << number;

	return ss.str();
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

void printTitle()
{
	std::cout << "\n\t\t\t---GeometryTool---\n";
}

void printMainMenu()
{
	std::cout << "\nEnter a number corresponding to the option you want to choose or enter \"exit\" if you want to exit:\n";

	std::cout << " " << SAVE_OR_DELETE_CORRESPONDING_NUMBER << " - save a line or a point or delete one;\n"
		<< " " << DEFINE_LINE_CORRESPONDING_NUMBER << " - define a line through slope and points;\n"
		<< " " << CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER << " - check if a point is on a line;\n"
		<< " " << FIND_PARALEL_LINE_CORRESPONDING_NUMBER << " - derive an equation of a line that is parallel to a given line and passes through a point;\n"
		<< " " << FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER << " - derive an equation of a perpendicular line to a given line and passes through a point;\n"
		<< " " << FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER << " - find intersection points (if it exists);\n"
		<< " " << FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER << " - find equations in triangle;\n"
		<< " " << FIND_THE_TANGENT_CORRESPONDING_NUMBER << " - derive an equation of a tangent to a parabola at a corresponding point;\n"
		<< " " << DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER << " - given four equations to determine the type of tetragon.\n";
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

void saveLine(const std::string name, const double k, double n)
{
	std::string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	std::ofstream  dataBase(linesDB, std::fstream::app);

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

void getAnswer(std::string& answer, std::string question)
{
	std::cout << question;
	std::getline(std::cin, answer);
	convertToLowerCase(answer);

	if (answer != "no" && answer != "yes")
	{
		std::cerr << INVALID_INPUT_TEXT;
		getAnswer(answer, question);
	}
}

void getName(std::string& name)
{
	std::cout << ENTER_NAME_TEXT;
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

		if (isElementInDatabase(name, linesDB))
		{
			std::cout << NAME_EXISTS_TEXT;
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

		if (isElementInDatabase(name, pointsDB))
		{
			std::cerr << NAME_EXISTS_TEXT;
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

		if (isElementInDatabase(name, pointsDB))
		{
			loadAnimation();
			getPoint(name, point);
		}
		else
		{
			std::cerr << NAME_DOESNT_EXIST_TEXT;
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

		if (isElementInDatabase(name, linesDB))
		{
			loadAnimation();
			getEquationOfLine(name, line);
		}
		else
		{
			std::cerr << NAME_DOESNT_EXIST_TEXT;
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

void defineLineThroughSlopeAndPoint()
{
	double k = 0, x = 0, y = 0;
	getSlope(k);

	getPointCoordinates(x, y);

	double n = k * x - y;

	calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}

std::string calculateLineByTwoPoints(double& k, double& n, double x1, double y1, double x2, double y2)
{
	std::string message;
	if (x1 == x2)
	{
		k = 1;
		n = -x1;
		message = "equalX";
	}
	else if (y1 == y2)
	{
		k = 0;
		n = y1;
		message = "equalY";
	}
	else
	{
		k = (y1 - y2) / (x1 - x2);
		n = k * x1 - y1;
		message = "passed";
	}
	return message;
}

void defineLineThroughPoints()
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	getPointCoordinates(x1, y1);

	getPointCoordinates(x2, y2);

	if (x1 == x2 && y1 == y2)
	{
		std::cerr << "Can't define a line! Points are the same!\n";
	}
	else
	{
		calcAnimation();
		double k = 0, n = 0;

		std::string message = calculateLineByTwoPoints(k, n, x1, y1, x2, y2);
		printLine(k, n, x1, y1, x2, y2);
		if (message == "equalX")
		{
			std::cerr << "The program cannot save lines that has equal x-coordinates! We're sorry...";
		}
		else if (message == "equalY")
		{
			std::cerr << "The program cannot save lines that has equal y-coordinates! We're sorry...";
		}
		else if (message == "passed")
		{
			wantToSaveLine(k, n);
		}
	}
}

void defineLineOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "slope")
	{
		defineLineThroughSlopeAndPoint();
	}
	else if (keyword == "points")
	{
		defineLineThroughPoints();
	}
	else if (keyword != "menu")
	{
		std::cerr << INVALID_INPUT_TEXT;
		defineLineOption();
	}
}

void findParallelLineOption()
{
	double k, n;

	getLineArguments(k, n);

	double x, y;

	getPointCoordinates(x, y);

	n = k * x - y;

	calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}

void findPerpendicularLineOption()
{
	double k, n;

	getLineArguments(k, n);

	double x, y;

	getPointCoordinates(x, y);

	calculatePerpendicularLineArgs(k, n, x, y);

	calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}

void findIntersectionPointOfParabolaAndLine()
{
	double k, n;

	getLineArguments(k, n);

	double p;

	getParabola(p);

	calcAnimation();
	if (p == 0)
	{
		double y = 0;
		double x = -n / k;

		std::cout << "There is one intersection point:\n"
			<< " Intersection point: (" << x << ", " << y << ")\n";
	}
	else
	{
		double a = k * k;
		double b = 2 * n * k - 2 * p;
		double c = n * n;
		double determinant = b * b - 4 * a * c;
		double x1 = (-b + sqrt(determinant)) / (2 * a);
		double x2 = (-b - sqrt(determinant)) / (2 * a);

		bool isX1IntersectionPoint = ((a * x1 * x1) + (b * x1) + c == 0);
		bool isX2IntersectionPoint = ((a * x2 * x2) + (b * x2) + c == 0);

		if ((x1 == x2 && isX1IntersectionPoint && isX2IntersectionPoint) || (isX1IntersectionPoint && !isX2IntersectionPoint))
		{
			double y1 = k * x1 - n;
			std::cout << "There is one intersection point:\n"
				<< " Intersection point: (" << x1 << ", " << y1 << ")\n";
		}
		else if (isX1IntersectionPoint && isX2IntersectionPoint)
		{
			double y1 = k * x1 - n;
			double y2 = k * x2 - n;

			std::cout << "There are two intersection points:\n"
				<< " Intersection point #1: (" << x1 << ", " << y1 << ")\n"
				<< " Intersection point #2: (" << x2 << ", " << y2 << ")\n";
		}
		else if (isX2IntersectionPoint)
		{
			double y2 = k * x2 - n;
			std::cout << "There is one intersection point:\n"
				<< " Intersection point: (" << x2 << ", " << y2 << ")\n";
		}
		else
		{
			std::cout << "There are no intersection points!\n";
		}
	}
}

void checkIfPointIsOnLineOption()
{
	double k = 0, n = 0;

	getLineArguments(k, n);

	double x = 0, y = 0;

	getPointCoordinates(x, y);

	bool isPointOnLine = ((k * x + n) == y) ? true : false;

	calcAnimation();
	if (isPointOnLine)
	{
		std::cout << "The point IS on the line.\n";
	}
	else
	{
		std::cout << "The point IS NOT on the line.\n";
	}
}

void findIntersectionPointOfTwoLines()
{
	double k1, n1;

	getLineArguments(k1, n1);

	double k2, n2;

	getLineArguments(k2, n2);

	calcAnimation();

	if (areLinesTheSame(k1, n1, k2, n2))
	{
		std::cerr << "The lines are the same! Incorrect input!\n";
	}
	else if (k1 == k2)
	{
		std::cout << "There are no intersection points! The lines are parallel!\n";
	}
	else
	{
		double x = 0, y = 0;
		calculateIntersectionPointOfTwoLines(x, y, k1, n1, k2, n2);
		std::cout << "The intersection point is: (" << x << ", " << y << ").\n";

		wantToSavePoint(x, y);
	}
}

void findIntersectionPointOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "parabola")
	{
		findIntersectionPointOfParabolaAndLine();
	}
	else if (keyword == "lines")
	{
		findIntersectionPointOfTwoLines();
	}
	else if (keyword != "menu")
	{
		std::cerr << INVALID_INPUT_TEXT;
		findIntersectionPointOption();
	}
}

void findEquationsInTriangleOption()
{
	std::string pointA;
	double xa, ya;

	std::cout << "Point A:\n";
	getPointCoordinates(xa, ya);

	std::string pointB;
	double xb, yb;

	std::cout << "Point B:\n";
	getPointCoordinates(xb, yb);

	std::string pointC;
	double xc, yc;

	std::cout << "Point C:\n";
	getPointCoordinates(xc, yc);

	calcAnimation();
	if (arePointsTheSame(xa, ya, xb, yb) || arePointsTheSame(xc, yc, xb, yb) || arePointsTheSame(xa, ya, xc, yc))
	{
		std::cerr << "Two of the points are the same! The program cannot create a triangle!";
	}
	else if (arePointsOnTheSameLine(xa, ya, xb, yb, xc, yc))
	{
		std::cerr << "The points are on the same line! The program cannot create a triangle!";
	}
	else
	{
		calculateHeights(xa, ya, xb, yb, xc, yc);
		wait();
		calculateMedians(xa, ya, xb, yb, xc, yc);
		wait();
		calculateSemetrals(xa, ya, xb, yb, xc, yc);
	}
}

void findTangentOption()
{
	double p, x, y;

	getParabola(p);

	getPointCoordinates(x, y);

	if ((y * y) == (2 * p * x))
	{
		double k = p / x;
		double n = (p * x) / y;

		std::cout << "Tangent:\n";
		printLine(k, n, x, y);
	}
	else
	{
		std::cout << "Point is not on the parabola! Can't find the tangent!\n";
	}
}

void findTheTypeOfTetragonOption()
{
	double k1, n1,
		k2, n2,
		k3, n3,
		k4, n4;

	std::cout << "Line 1:\n";
	getLineArguments(k1, n1);
	std::cout << "Line 2:\n";
	getLineArguments(k2, n2);
	std::cout << "Line 3:\n";
	getLineArguments(k3, n3);
	std::cout << "Line 4:\n";
	getLineArguments(k4, n4);

	calcAnimation();
	if (checkIfTetragonCanBeCreated(k1, n1, k2, n2, k3, n3, k4, n4))
	{
		if (isTetragonRectangle(k1, k2, k3, k4) || isTetragonRectangle(k2, k1, k3, k4) ||
			isTetragonRectangle(k3, k1, k2, k4) || isTetragonRectangle(k4, k1, k2, k3))
		{
			if (areAllSidesEqual(k1, n1, k2, n2, k3, n3, k4, n4) || areAllSidesEqual(k2, n2, k1, n1, k3, n3, k4, n4) ||
				areAllSidesEqual(k3, n3, k1, n1, k2, n2, k4, n4) || areAllSidesEqual(k4, n4, k1, n1, k2, n2, k3, n3))
			{
				std::cout << "The teragon is a SQUARE!\n";
			}
			else
			{
				std::cout << "The tetragon is a RECTANGLE!\n";
			}
		}
		else
		{
			if ((k1 == k2 && k3 == k4) ||
				(k1 == k3 && k2 == k4) ||
				(k1 == k4 && k2 == k3))
			{
				if (areAllSidesEqual(k1, n1, k3, n3, k2, n2, k4, n4) ||
					areAllSidesEqual(k1, n1, k2, n2, k3, n3, k4, n4) ||
					areAllSidesEqual(k1, n1, k2, n2, k4, n4, k3, n3) ||
					areAllSidesEqual(k2, n2, k1, n1, k3, n3, k4, n4) ||
					areAllSidesEqual(k2, n2, k1, n1, k4, n4, k3, n3) ||
					areAllSidesEqual(k3, n3, k1, n1, k4, n4, k2, n2))
				{
					std::cout << "The tetragon is a RHOMBUS!\n";
				}
				else
				{
					std::cout << "The tetragon is a PARALLELOGRAM!\n";
				}
			}
			else if (k1 == k2 || k1 == k3 ||
				k1 == k4 || k2 == k3 ||
				k2 == k4 || k3 == k4)
			{
				std::cout << "The tetragon is a TRAPEZOID!\n";
			}
			else
			{
				std::cout << "It is just a tetragon!\n";
			}
		}
	}
}

void usersChoice()
{
	std::cout << "Enter an option: ";

	std::string option;
	std::getline(std::cin, option);

	convertToLowerCase(option);

	if (option == SAVE_OR_DELETE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nSave or delete:\n"
			<< "Enter the word \"save\" if you want to save a line or a point\n"
			<< "Enter the word \"delete\" if you want to delete a line or a point\n"
			<< GO_TO_MAIN_MENU_TEXT;
		saveOrDeleteOption();

		wait();
		printMainMenu();
	}
	else if (option == DEFINE_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nDefine line:\n"
			<< "Enter the word \"slope\" if you want to define a line through slope and a point\n"
			<< "Enter the word \"points\" if you want to define a line through two points\n"
			<< GO_TO_MAIN_MENU_TEXT;
		defineLineOption();

		wait();
		printMainMenu();
	}
	else if (option == CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nCheck if a point is on a line:\n";
		checkIfPointIsOnLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_PARALEL_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind parallel line:\n";
		findParallelLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind perpendicular line:\n";
		findPerpendicularLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER)
	{
		std::cout << "\nEnter the word \"parabola\" if you want to find the intersection point(s) of a parabola and a line\n"
			<< "Enter the word \"lines\" if you want to find the intersection point(s) of two lines\n"
			<< GO_TO_MAIN_MENU_TEXT;
		findIntersectionPointOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind equations in trinagle by given three points:\n";
		findEquationsInTriangleOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_THE_TANGENT_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind the tangent of a parabola at a point:\n";
		findTangentOption();

		wait();
		printMainMenu();
	}
	else if (option == DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind the type of tetragon: \n";
		findTheTypeOfTetragonOption();

		wait();
		printMainMenu();
	}
	else if (option == "exit")
	{
		stopProgram = true;
	}
	else
	{
		std::cerr << INVALID_INPUT_TEXT;
		usersChoice();
	}
}

int main()
{
	printTitle();
	printMainMenu();

	while (!stopProgram)
	{
		usersChoice();
	}

	closeAnimation();

	return 0;
}