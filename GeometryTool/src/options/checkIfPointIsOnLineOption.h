#pragma once

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
