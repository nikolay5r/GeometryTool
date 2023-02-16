#pragma once

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

void splitByDelim(std::vector<std::string>& words, std::string text, std::string delim = " ")
{
	size_t pos = 0;

	while ((pos = text.find(delim)) != std::string::npos) {
		words.push_back(text.substr(0, pos));
		text.erase(0, pos + delim.length());
	}

	words.push_back(text);
}

void convertToLowerCase(std::string& text)
{
	std::string result = "";

	for (int i = 0; i < text.length(); i++) {

		char ch = tolower(text[i]);

		result += ch;
	}

	text = result;
}

void calculatePerpendicularLineArgs(double& k, double& n, double& x, double& y)
{
	k = -1 / k;
	n = k * x - y;
}

void calculateIntersectionPointOfTwoLines(double& x, double& y, double k1, double n1, double k2, double n2)
{
	x = (n2 - n1) / (k1 - k2);
	y = k1 * x - n1;
}

void calculateHeights(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	std::cout << "Heights:\n";

	calculateLineByTwoPoints(k, n, xa, ya, xb, yb);
	calculatePerpendicularLineArgs(k, n, xc, yc);

	std::cout << " #1: ";
	printLine(k, n, xc, yc);

	calculateLineByTwoPoints(k, n, xa, ya, xc, yc);
	calculatePerpendicularLineArgs(k, n, xb, yb);

	std::cout << " #2: ";
	printLine(k, n, xb, yb);

	calculateLineByTwoPoints(k, n, xb, yb, xc, yc);
	calculatePerpendicularLineArgs(k, n, xa, ya);

	std::cout << " #3: ";
	printLine(k, n, xa, ya);
}

void calculateMedians(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	std::cout << "Medians:\n";

	double xm = (xa + xb) / 2;
	double ym = (ya + yb) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xc, yc);

	std::cout << " #1: ";
	printLine(k, n, xc, yc);

	xm = (xa + xc) / 2;
	ym = (ya + yc) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xb, yb);

	std::cout << " #2: ";
	printLine(k, n, xb, yb);

	xm = (xb + xc) / 2;
	ym = (yb + yc) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xa, ya);

	std::cout << " #3: ";
	printLine(k, n, xa, ya);
}

void calculateSemetrals(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	std::cout << "Semetrals:\n";

	double xm = (xa + xb) / 2;
	double ym = (ya + yb) / 2;
	calculateLineByTwoPoints(k, n, xa, ya, xb, yb);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	std::cout << " #1: ";
	printLine(k, n, xm, ym);

	xm = (xa + xc) / 2;
	ym = (ya + yc) / 2;
	calculateLineByTwoPoints(k, n, xa, ya, xc, yc);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	std::cout << " #2: ";
	printLine(k, n, xm, ym);

	xm = (xb + xc) / 2;
	ym = (yb + yc) / 2;
	calculateLineByTwoPoints(k, n, xb, yb, xc, yc);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	std::cout << " #3: ";
	printLine(k, n, xm, ym);
}

std::string toString(double number)
{
	std::stringstream ss;
	ss << number;

	return ss.str();
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
