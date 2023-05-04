#include "UserInteraction.h"
#include "Constants.h"
#include "Animation.h"
#include "Helper.h"
#include "LineService.h"
#include "PointService.h"
#include "Validation.h"
#include "Print.h"

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
		std::cerr << constants::INVALID_INPUT_TEXT;
		findIntersectionPointOption();
	}
}

void determineTheTypeOfTetragonOption()
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
		std::cerr << constants::INVALID_INPUT_TEXT;
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


void savePointOption(std::string name = "")
{
	double x = 0,
		y = 0;

	if (name == "")
	{
		std::cout << constants::ENTER_NAME_TEXT;
		std::getline(std::cin, name);
	}

	if (!isNameValid(name))
	{
		savePointOption();
	}
	else if (isElementInDatabase(name, constants::pointsDB))
	{
		std::cerr << constants::NAME_EXISTS_TEXT;
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
		std::cout << constants::ENTER_NAME_TEXT;
		std::getline(std::cin, name);
	}

	if (!isNameValid(name))
	{
		saveLineOption();
	}
	else if (isElementInDatabase(name, constants::linesDB))
	{
		std::cerr << constants::NAME_EXISTS_TEXT;
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
		std::cerr << constants::INVALID_INPUT_TEXT;
		saveOption();
	}
}

void deleteLineOption()
{
	std::string name;

	std::cout << "Enter the name of the line: ";
	std::getline(std::cin, name);

	if (!isElementInDatabase(name, constants::linesDB))
	{
		std::cerr << constants::NAME_DOESNT_EXIST_TEXT;
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

	if (!isElementInDatabase(name, constants::pointsDB))
	{
		std::cerr << constants::NAME_DOESNT_EXIST_TEXT;
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
		std::cerr << constants::INVALID_INPUT_TEXT;
	}
}

void saveOrDeleteOption()
{
	std::string keyword = getKeywordFromConsole();

	if (keyword == "save")
	{
		std::cout << "Enter \"line\" if you want to save a line\n"
			<< "Enter \"point\" if you want to save a point\n"
			<< constants::GO_TO_MAIN_MENU_TEXT;

		saveOption();
	}
	else if (keyword == "delete")
	{
		std::cout << "Enter \"line\" if you want to delete a line\n"
			<< "Enter \"point\" if you want to delete a point\n"
			<< constants::GO_TO_MAIN_MENU_TEXT;

		deleteOption();
	}
	else if (keyword != "menu")
	{
		std::cerr << constants::INVALID_INPUT_TEXT;
		saveOrDeleteOption();
	}
}
