#pragma once

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
