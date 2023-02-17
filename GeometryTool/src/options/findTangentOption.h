#pragma once

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
