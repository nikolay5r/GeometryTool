#pragma once

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
