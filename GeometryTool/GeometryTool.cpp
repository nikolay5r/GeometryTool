
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <string.h>
#include <string>
#include <windows.h>

const int timeToWait = 1200;
const int maxLengthOfName = 16;
const int maxNumberSize = 100;

const char* linesDB = "lines.txt";

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

#include "headers/print.h"
#include "headers/animation.h"
#include "headers/helper.h"
#include "headers/validation.h"
#include "headers/gsw.h"
#include "headers/services/pointService.h"
#include "headers/services/lineService.h"
#include "headers/options/saveAndDeleteOption.h"

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