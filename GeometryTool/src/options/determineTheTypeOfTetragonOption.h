#pragma once

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
