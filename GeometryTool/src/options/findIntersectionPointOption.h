#pragma once

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
		std::cerr << INVALID_INPUT_TEXT;
		findIntersectionPointOption();
	}
}
