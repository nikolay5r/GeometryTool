#pragma once

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
