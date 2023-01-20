/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Nikolay Radilov
* @idnumber 3MI0600253
* @compiler VC
*
*
*
*/


#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <string.h>
#include <cstring>
//#include <windows.h>

using namespace std;
using std::cin;
using std::cout;

//const int timeToWait = 1200;
const int maxLengthOfName = 16;
const int maxNumberSize = 100;

const char* linesDB = "lines.txt";
const char* pointsDB = "points.txt";

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
const char* DATABASE_CANNOT_OPEN_TEXT	 = "ERROR! We are sorry the database cannot be open!\n";
const char* ENTER_NAME_TEXT = "Enter name (it can be upper and lower case letters, \'_\' and numbers and 16 characters long): \n";
const char* NAME_EXISTS_TEXT = "Name already exists! Try another. . .\n";
const char* NAME_DOESNT_EXIST_TEXT = "Name doesn't exist! Try another. . .\n";
const char* INVALID_NUMBER_TEXT = "Number is too large! It should be between -100 and 100!\n";

bool stopProgram = false;


bool isInputNumber(string input)
{
	int counterDots = 0;
	int index = 0;

	if (input[0] == '-')
	{
		index++;
	}

	for ( ; index < input.length(); index++)
	{
		char currentChar = input[index];
		if (currentChar == '.' || currentChar == ',')
		{
			counterDots++;
		}

		if (counterDots > 1 || (currentChar < '0' || currentChar > '9'))
		{
			cerr << INVALID_INPUT_TEXT;
			return false;
		}
	}

	return true;
}

bool isNumberValid(const double number)
{
	if (abs(number) <= maxNumberSize)
	{
		return true;
	}
	cerr << INVALID_NUMBER_TEXT;
	return false;
}

bool isNameValid(const string name)
{
	if (name.length() > maxLengthOfName)
	{
		cerr << "The name is too long! Try again...\n";
		return false;
	}

	for (int i = 0; i < name.length(); i++)
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= '0' && name[i] <= '9')
			|| name[i] == '_'))
		{
			cerr << "Invalid characters in name! Try again...\n";
			return false;
		}
	}

	return true;
}

void printLine(const double k, double n, const double x1, const double y1, const double x2 = 102, const double y2 = 102)
{
	string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	cout << "The equation of the line is: ";

	if (x1 == x2)
	{
		cout << "x = " << x1;
	}
	else if (y1 == y2)
	{
		cout << "y = " << y1;
	}
	else if (k != 1 && k != 0)
	{
		if (n == 0)
		{
			cout << "y = " << k << " * x";
		}
		else
		{
			cout << "y = " << k << " * x " << symbol << " " << n;
		}
	}
	else if (k == 1)
	{
		cout << "y = x " << symbol << " " << n;
	}
	else
	{
		if (symbol == "+")
		{
			cout << "y = " << n;
		}
		else
		{
			cout << "y = " << symbol << n;
		}
	}

	cout << "\n";
}

void getN(double& n)
{
	string stringN;
	cout << "Enter n: ";
	getline(cin, stringN);
	if (!isInputNumber(stringN))
	{
		getN(n);
	}
	else
	{
		n = stod(stringN);
		if (!isNumberValid(n))
		{
			getN(n);
		}
	}
}

void getSlope(double& k)
{
	string stringK;
	cout << "Enter slope (k): ";
	getline(cin, stringK);
	if (!isInputNumber(stringK))
	{
		getSlope(k);
	}
	else
	{
		k = stod(stringK);
		if (!isNumberValid(k))
		{
			getSlope(k);
		}
	}
}

void convertToLowerCase(string& text)
{
	string result = "";

	for (int i = 0; i < text.length(); i++) {

		char ch = tolower(text[i]);

		result += ch;
	}

	text = result;
}

string toString(double number)
{
	stringstream ss;
	ss << number;

	return ss.str();
}

string getKeywordFromConsole()
{
	cout << "Keyword: ";

	string keyword = "";

	getline(cin, keyword);

	cout << "\n";

	convertToLowerCase(keyword);

	return keyword;
}

//ANIMATIONS ONLY WORK WITH <windows.h>

//void wait()
//{
//	Sleep(timeToWait);
//}
 
//void printThreeDotsAnimation()
//{
//	for (int i = 0; i < 3; i++)
//	{
//		wait();
//		cout << ". ";
//	}
//
//	wait();
//	cout << "\n";
//}

//void calcAnimation()
//{
//	cout << "Calculating";
//	printThreeDotsAnimation();
//}

//void loadAnimation()
//{
//	cout << "Loading";
//	printThreeDotsAnimation();
//}

//void closeAnimation()
//{
//	cout << "Closing program";
//	printThreeDotsAnimation();
//}

//void saveAnimation()
//{
//	cout << "Saving";
//	printThreeDotsAnimation();
//}

//void deleteAnimation()
//{
//	cout << "Deleting";
//	printThreeDotsAnimation();
//}

void splitByDelim(vector<string>& words, string text, string delim = " ")
{
	size_t pos = 0;

	while ((pos = text.find(delim)) != string::npos) {
		words.push_back(text.substr(0, pos));
		text.erase(0, pos + delim.length());
	}

	words.push_back(text);
}

void showTitle()
{
	cout << "\n\t\t\t---GeometryTool---\n";
}

void showMainMenu()
{
	cout << "\nEnter a number corresponding to the option you want to choose or enter \"exit\" if you want to exit:\n";

	cout << " " << SAVE_OR_DELETE_CORRESPONDING_NUMBER << " - save a line or a point or delete one;\n"
		<< " " << DEFINE_LINE_CORRESPONDING_NUMBER << " - define a line through slope and points;\n"
		<< " " << CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER << " - check if a point is on a line;\n"
		<< " " << FIND_PARALEL_LINE_CORRESPONDING_NUMBER << " - derive an equation of a line that is parallel to a given line and passes through a point;\n"
		<< " " << FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER << " - derive an equation of a perpendicular line to a given line and passes through a point;\n"
		<< " " << FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER << " - find intersection points (if it exists);\n"
		<< " " << FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER << " - find equations in triangle;\n"
		<< " " << FIND_THE_TANGENT_CORRESPONDING_NUMBER << " - derive an equation of a tangent to a parabola at a corresponding point;\n"
		<< " " << DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER << " - given four equations to determine the type of tetragon.\n";
}

void getEquationOfLine(const string name, string& equation)
{
	ifstream database(linesDB);

	if (database.is_open())
	{
		string rowText;

		while (getline(database, rowText))
		{
			vector<string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				equation = words[1];
				break;
			}
		}

		database.close();
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void getPoint(const string name, string& point)
{
	ifstream database(pointsDB);

	if (database.is_open())
	{
		string rowText;

		while (getline(database, rowText))
		{
			vector<string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				point = words[1];
			}
		}

		database.close();
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

bool isElementInDatabase(const string element, const char* path)
{
	ifstream dataBase(path);

	if (dataBase.is_open())
	{
		string rowText;

		while (getline(dataBase, rowText))
		{
			vector<string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == element)
			{
				dataBase.close();
				return true;
			}
		}
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}

	dataBase.close();
	return false;
}

void saveLine(const string name, const double k, double n)
{
	string symbol = n >= 0 ? "+" : "-";
	n = abs(n);
	ofstream dataBase(linesDB, fstream::app);

	if (dataBase.is_open())
	{
		string data = name + " : " + toString(k) + "*x" + symbol + toString(n);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void getXCoord(double& x)
{
	string stringX;
	cout << "x: ";
	getline(cin, stringX);

	if (!isInputNumber(stringX))
	{
		getXCoord(x);
	}
	else
	{
		x = stod(stringX);
		if (!isNumberValid(x))
		{
			getXCoord(x);
		}
	}
}

void getYCoord(double& y)
{
	string stringY;
	cout << "y: ";
	getline(cin, stringY);

	if (!isInputNumber(stringY))
	{
		getYCoord(y);
	}
	else
	{
		y = stod(stringY);
		if (!isNumberValid(y))
		{
			getYCoord(y);
		}
	}
}

void setEquationOfLine(double& k, double& n)
{
	cout << "Enter the equation of the line using this format \"k*x + n\"\n";
	getSlope(k);
	getN(n);
}

void setPointCoordinates(double& x, double& y)
{
	string stringX,
		stringY;

	cout << "Enter coordinates:\n";
	
	getXCoord(x);
	getYCoord(y);
}

void saveLineOption(string name = "")
{
	double k, n;

	if (name == "")
	{
		cout << ENTER_NAME_TEXT;
		getline(cin, name);
	}

	if (!isNameValid(name))
	{
		saveLineOption();
	}
	else if (isElementInDatabase(name, linesDB))
	{
		cerr << NAME_EXISTS_TEXT;
		saveLineOption();
	}
	else
	{
		setEquationOfLine(k, n);
		saveLine(name, k, n);
	}
}

void savePoint(const string name, const double x, const double y)
{
	ofstream dataBase(pointsDB, ios::app);

	if (dataBase.is_open())
	{
		string data = name + " : " + toString(x) + ";" + toString(y);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void savePointOption(string name = "")
{
	double x = 0,
		y = 0;

	if (name == "")
	{
		cout << ENTER_NAME_TEXT;
		getline(cin, name);
	}

	if (!isNameValid(name))
	{
		savePointOption();
	}
	else if (isElementInDatabase(name, pointsDB))
	{
		cerr << NAME_EXISTS_TEXT;
		savePointOption();
	}
	else
	{
		setPointCoordinates(x, y);
		savePoint(name, x, y);
	}
}

void saveOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		saveLineOption();
		//saveAnimation();
	}
	else if (keyword == "point")
	{
		savePointOption();
		//saveAnimation();
	}
	else if (keyword != "menu")
	{
		cerr << INVALID_INPUT_TEXT;
		saveOption();
	}
}

void deleteLine(const string name)
{
	string rowText;

	ifstream dataBase(linesDB);
	ofstream newDataBase("linesNew.txt");

	if (dataBase.is_open() && newDataBase.is_open())
	{
		while (getline(dataBase, rowText))
		{
			vector<string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				continue;
			}

			newDataBase << rowText << "\n";
		}

		dataBase.close();
		newDataBase.close();

		remove(linesDB);
		if (rename("linesNew.txt", linesDB))
		{
			stopProgram = true;
			cerr << "There was an error with the deleting of the line!\nWe are sorry. . .\n";
		}
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void deleteLineOption()
{
	string name;

	cout << "Enter the name of the line: ";
	getline(cin, name);

	if (!isElementInDatabase(name, linesDB))
	{
		cerr << NAME_DOESNT_EXIST_TEXT;
		deleteLineOption();
	}
	else
	{
		deleteLine(name);
	}
}

void deletePoint(const string name)
{
	string rowText;

	ifstream dataBase(pointsDB);
	ofstream newDataBase("pointsNew.txt");

	if (dataBase.is_open() && newDataBase.is_open())
	{
		while (getline(dataBase, rowText))
		{
			vector<string> words{};

			splitByDelim(words, rowText, " : ");

			if (words[0] == name)
			{
				continue;
			}

			newDataBase << rowText << "\n";
		}

		dataBase.close();
		newDataBase.close();

		remove(pointsDB);
		if (rename("pointsNew.txt", pointsDB) != 0)
		{
			stopProgram = true;
			cerr << "There was an error with the deleting of the point!\nWe are sorry. . .\n";
		}
	}
	else
	{
		cerr << DATABASE_CANNOT_OPEN_TEXT;
		exit(0);
	}
}

void deletePointOption()
{
	string name;

	cout << "Enter the name of the point: ";
	getline(cin, name);

	if (!isElementInDatabase(name, pointsDB))
	{
		cerr << NAME_DOESNT_EXIST_TEXT;
		deletePointOption();
	}
	else
	{
		deletePoint(name);
	}
}

void deleteOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		deleteLineOption();
		//deleteAnimation();
	}
	else if (keyword == "point")
	{
		deletePointOption();
		//deleteAnimation();
	}
	else if (keyword != "menu")
	{
		cerr << INVALID_INPUT_TEXT;
	}
}

void saveOrDeleteOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "save")
	{
		cout << "Enter \"line\" if you want to save a line\n"
			<< "Enter \"point\" if you want to save a point\n"
			<< GO_TO_MAIN_MENU_TEXT;

		saveOption();
	}
	else if (keyword == "delete")
	{
		cout << "Enter \"line\" if you want to delete a line\n"
			<< "Enter \"point\" if you want to delete a point\n"
			<< GO_TO_MAIN_MENU_TEXT;

		deleteOption();
	}
	else if (keyword != "menu")
	{
		cerr << INVALID_INPUT_TEXT;
		saveOrDeleteOption();
	}
}

void getAnswer(string& answer, string question)
{	
	cout << question;
	getline(cin, answer);
	convertToLowerCase(answer);

	if (answer != "no" && answer != "yes")
	{
		cerr << INVALID_INPUT_TEXT;
		getAnswer(answer, question);
	}
}

void getName(string& name)
{
	cout << ENTER_NAME_TEXT;
	getline(cin, name);
	if (!isNameValid(name))
	{
		getName(name);
	}
}

void wantToSaveLine(const double k, const double n, string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to save the line? ");
	}

	if (answer == "yes")
	{
		string name;
		getName(name);

		if (isElementInDatabase(name, linesDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToSaveLine(k, n, answer);
		}
		else
		{
			//saveAnimation();
			saveLine(name, k, n);
		}
	}
}

void wantToSavePoint(const double x, const double y, string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to save the point? ");
	}

	if (answer == "yes")
	{
		string name;
		getName(name);

		if (isElementInDatabase(name, pointsDB))
		{
			cerr << NAME_EXISTS_TEXT;
			wantToSavePoint(x, y, answer);
		}
		else
		{
			savePoint(name, x, y);
			//saveAnimation();
		}
	}
}

void wantToUseExistingPoint(string& point, string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to use existing point? ");
	}

	if (answer == "yes")
	{
		string name;
		getName(name);

		if (isElementInDatabase(name, pointsDB))
		{
			//loadAnimation();
			getPoint(name, point);
		}
		else
		{
			cerr << NAME_DOESNT_EXIST_TEXT;
			wantToUseExistingPoint(point, answer);
		}
	}
}

void wantToUseExistingLine(string& line, string answer = "")
{
	if (answer == "")
	{
		getAnswer(answer, "Do you want to use existing line? ");
	}

	if (answer == "yes")
	{
		string name;
		getName(name);

		if (isElementInDatabase(name, linesDB))
		{
			//loadAnimation();
			getEquationOfLine(name, line);
		}
		else
		{
			cerr << NAME_DOESNT_EXIST_TEXT;
			wantToUseExistingLine(line, answer);
		}
	}
}

void getCoordinatesFromExistingPoint(string point, double& x, double& y)
{
	vector<string> coordinates;
	splitByDelim(coordinates, point, ";");

	x = stod(coordinates[0]);
	y = stod(coordinates[1]);
}

void getArgumentsFromExistingLine(string equation, double& k, double& n)
{
	vector<string> arguments;
	splitByDelim(arguments, equation, "*x");

	k = stod(arguments[0]);
	n = stod(arguments[1]);
}

void getLineArguments(double& k, double& n)
{
	string line = "";

	wantToUseExistingLine(line);

	if (line == "")
	{
		setEquationOfLine(k, n);
		wantToSaveLine(k, n);
	}
	else
	{
		getArgumentsFromExistingLine(line, k, n);
	}
}

void getPointCoordinates(double& x, double& y)
{
	string point = "";
	wantToUseExistingPoint(point);

	if (point == "")
	{
		setPointCoordinates(x, y);
		wantToSavePoint(x, y);
	}
	else
	{
		getCoordinatesFromExistingPoint(point, x, y);
	}
}

void getParabola(double& p)
{
	cout << "Enter a parabola in this format \"y^2 = 2px\":\n";
	cout << "p: ";
	cin >> p;
	if (!isNumberValid(p))
	{
		cerr << "P-argument is too large! It should be between -100 and 100!\n";
	}
}

void defineLineThroughSlopeAndPoint()
{
	double k = 0, x = 0, y = 0;
	getSlope(k);
	
	getPointCoordinates(x, y);

	double n = k * x - y;

			//calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}

string calculateLineByTwoPoints(double& k, double& n, double x1, double y1, double x2, double y2)
{
	string message;
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

void defineLineThroughPoints()
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	getPointCoordinates(x1, y1);

	getPointCoordinates(x2, y2);

	if (x1 == x2 && y1 == y2)
	{
		cerr << "Can't define a line! Points are the same!\n";
	}
	else
	{
		//calcAnimation();
		double k = 0, n = 0;

		string message = calculateLineByTwoPoints(k, n, x1, y1, x2, y2);
		printLine(k, n, x1, y1, x2, y2);
		if (message == "equalX")
		{
			cerr << "The program cannot save lines that has equal x-coordinates! We're sorry...";
		}
		else if (message == "equalY")
		{
			cerr << "The program cannot save lines that has equal y-coordinates! We're sorry...";
		}
		else if (message == "passed")
		{
			wantToSaveLine(k, n);
		}
	}
}

void defineLineOption()
{
	string keyword = getKeywordFromConsole();

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
		cerr << INVALID_INPUT_TEXT;
		defineLineOption();
	}
}

void checkIfPointIsOnLineOption()
{
	double k = 0, n = 0;

	getLineArguments(k, n);

	double x = 0, y = 0;

	getPointCoordinates(x, y);

	bool isPointOnLine = ((k * x + n) == y) ? true : false;

	//calcAnimation();
	if (isPointOnLine)
	{
		cout << "The point IS on the line.\n";
	}
	else
	{
		cout << "The point IS NOT on the line.\n";
	}
}

void calculatePerpendicularLineArgs(double& k, double& n, double& x, double& y)
{
	k = -1 / k;
	n = k * x - y;
}

void findParallelLineOption()
{
	double k, n;

	getLineArguments(k, n);

	double x, y;

	getPointCoordinates(x, y);

	n = k * x - y;

	//calcAnimation();
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

	//calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}

void findIntersectionPointOfParabolaAndLine()
{
	double k, n;

	getLineArguments(k, n);

	double p;

	getParabola(p);

	//calcAnimation();
	if (p == 0)
	{
		double y = 0;
		double x = -n / k;

		cout << "There is one intersection point:\n"
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
			cout << "There is one intersection point:\n"
				<< " Intersection point: (" << x1 << ", " << y1 << ")\n";
		}
		else if (isX1IntersectionPoint && isX2IntersectionPoint)
		{
			double y1 = k * x1 - n;
			double y2 = k * x2 - n;

			cout << "There are two intersection points:\n"
				<< " Intersection point #1: (" << x1 << ", " << y1 << ")\n"
				<< " Intersection point #2: (" << x2 << ", " << y2 << ")\n";
		}
		else if (isX2IntersectionPoint)
		{
			double y2 = k * x2 - n;
			cout << "There is one intersection point:\n"
				<< " Intersection point: (" << x2 << ", " << y2 << ")\n";
		}
		else
		{
			cout << "There are no intersection points!\n";
		}
	}
}

bool areLinesTheSame(double k1, double n1, double k2, double n2)
{
	return k1 == k2 && n1 == n2;
}

void calculateIntersectionPointOfTwoLines(double& x, double& y, double k1, double n1, double k2, double n2)
{
	x = (n2 - n1) / (k1 - k2);
	y = k1 * x - n1;
}

void findIntersectionPointOfTwoLines()
{
	double k1, n1;

	getLineArguments(k1, n1);

	double k2, n2;

	getLineArguments(k2, n2);

	//calcAnimation();

	if (areLinesTheSame(k1, n1, k2, n2))
	{
		cerr << "The lines are the same! Incorrect input!\n";
	}
	else if (k1 == k2)
	{
		cout << "There are no intersection points! The lines are parallel!\n";
	}
	else
	{
		double x = 0, y = 0;
		calculateIntersectionPointOfTwoLines(x, y, k1, n1, k2, n2);
		cout << "The intersection point is: (" << x << ", " << y << ").\n";

		wantToSavePoint(x, y);
	}
}

void findIntersectionPointOption()
{
	string keyword = getKeywordFromConsole();

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
		cerr << INVALID_INPUT_TEXT;
		findIntersectionPointOption();
	}
}

bool arePointsTheSame(double& x1, double& y1, double& x2, double& y2)
{
	return (x1 == x2 && y1 == y2);
}

bool arePointsOnTheSameLine(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double k, n;

	calculateLineByTwoPoints(k, n, x1, y1, x2, y2);

	return (y3 == k * x3 + n);
}

void calculateHeights(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	cout << "Heights:\n";

	calculateLineByTwoPoints(k, n, xa, ya, xb, yb);
	calculatePerpendicularLineArgs(k, n, xc, yc);

	cout << " #1: ";
	printLine(k, n, xc, yc);

	calculateLineByTwoPoints(k, n, xa, ya, xc, yc);
	calculatePerpendicularLineArgs(k, n, xb, yb);

	cout << " #2: ";
	printLine(k, n, xb, yb);

	calculateLineByTwoPoints(k, n, xb, yb, xc, yc);
	calculatePerpendicularLineArgs(k, n, xa, ya);

	cout << " #3: ";
	printLine(k, n, xa, ya);
}

void calculateMedians(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	cout << "Medians:\n";

	double xm = (xa + xb) / 2;
	double ym = (ya + yb) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xc, yc);

	cout << " #1: ";
	printLine(k, n, xc, yc);

	xm = (xa + xc) / 2;
	ym = (ya + yc) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xb, yb);

	cout << " #2: ";
	printLine(k, n, xb, yb);

	xm = (xb + xc) / 2;
	ym = (yb + yc) / 2;
	calculateLineByTwoPoints(k, n, xm, ym, xa, ya);

	cout << " #3: ";
	printLine(k, n, xa, ya);
}

void calculateSemetrals(double xa, double ya, double xb, double yb, double xc, double yc)
{
	double k, n;

	cout << "Semetrals:\n";

	double xm = (xa + xb) / 2;
	double ym = (ya + yb) / 2;
	calculateLineByTwoPoints(k, n, xa, ya, xb, yb);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	cout << " #1: ";
	printLine(k, n, xm, ym);

	xm = (xa + xc) / 2;
	ym = (ya + yc) / 2;
	calculateLineByTwoPoints(k, n, xa, ya, xc, yc);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	cout << " #2: ";
	printLine(k, n, xm, ym);

	xm = (xb + xc) / 2;
	ym = (yb + yc) / 2;
	calculateLineByTwoPoints(k, n, xb, yb, xc, yc);
	calculatePerpendicularLineArgs(k, n, xm, ym);

	cout << " #3: ";
	printLine(k, n, xm, ym);
}

void findEquationsInTriangleOption()
{
	string pointA;
	double xa, ya;

	cout << "Point A:\n";
	getPointCoordinates(xa, ya);

	string pointB;
	double xb, yb;

	cout << "Point B:\n";
	getPointCoordinates(xb, yb);

	string pointC;
	double xc, yc;

	cout << "Point C:\n";
	getPointCoordinates(xc, yc);

	//calcAnimation();
	if (arePointsTheSame(xa, ya, xb, yb) || arePointsTheSame(xc, yc, xb, yb) || arePointsTheSame(xa, ya, xc, yc))
	{
		cerr << "Two of the points are the same! The program cannot create a triangle!";
	}
	else if (arePointsOnTheSameLine(xa, ya, xb, yb, xc, yc))
	{
		cerr << "The points are on the same line! The program cannot create a triangle!";
	}
	else
	{
		calculateHeights(xa, ya, xb, yb, xc, yc);
		//wait();
		calculateMedians(xa, ya, xb, yb, xc, yc);
		//wait();
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

		cout << "Tangent:\n";
		printLine(k, n, x, y);
	}
	else
	{
		cout << "Point is not on the parabola! Can't find the tangent!\n";
	}
}

bool canCreateTetragon(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4)
{
	if ((areLinesTheSame(k1, n1, k2, n2) || areLinesTheSame(k1, n1, k3, n3)) ||
		(areLinesTheSame(k1, n1, k4, n4) || areLinesTheSame(k3, n3, k2, n2)) ||
		(areLinesTheSame(k4, n4, k2, n2) || areLinesTheSame(k3, n3, k4, n4)))
	{
		cerr << "You used the same line at least twice! Cannot create a tetragon!\n";
		return false;
	}

	if ((((k1 == k2) && (k2 == k3)) || ((k1 == k2) && (k2 == k4))) ||
		(((k1 == k3) && (k3 == k4)) || (k2 == k3) && (k3 == k4)))
	{
		cerr << "Cannot create a tetragon! At least three of the lines are parallel!\n";
		return false;
	}

	return true;
}

bool areLinesPerpendicular(double k1, double k2)
{
	return (k1 == (-1 / k2));
}

bool isTetragonRectangle(double k1, double k2, double k3, double k4)
{
	return (areLinesPerpendicular(k1, k2) && areLinesPerpendicular(k1, k3) && k1 == k4) ||
		(areLinesPerpendicular(k1, k2) && areLinesPerpendicular(k1, k4) && k1 == k3) ||
		(areLinesPerpendicular(k1, k3) && areLinesPerpendicular(k1, k4) && k1 == k2);
}

bool areAllSidesEqual(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4)
{
	double xa, ya,
		xb, yb,
		xc, yc,
		xd, yd;

	calculateIntersectionPointOfTwoLines(xa, ya, k1, n1, k4, n4);
	calculateIntersectionPointOfTwoLines(xb, yb, k1, n1, k2, n2);
	calculateIntersectionPointOfTwoLines(xc, yc, k2, n2, k3, n3);
	calculateIntersectionPointOfTwoLines(xd, yd, k3, n3, k4, n4);


	double AB = sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
	double AD = sqrt((xd - xa) * (xd - xa) + (yd - ya) * (yd - ya));
	double BC = sqrt((xc - xb) * (xc - xb) + (yc - yb) * (yc - yb));
	double CD = sqrt((xd - xc) * (xd - xc) + (yd - yc) * (yd - yc));

	return (AB == AD && AD == BC && BC == CD);
}

void findTheTypeOfTetragonOption()
{
	double k1, n1,
		k2, n2,
		k3, n3,
		k4, n4;

	cout << "Line 1:\n";
	getLineArguments(k1, n1);
	cout << "Line 2:\n";
	getLineArguments(k2, n2);
	cout << "Line 3:\n";
	getLineArguments(k3, n3);
	cout << "Line 4:\n";
	getLineArguments(k4, n4);

	//calcAnimation();
	if (canCreateTetragon(k1, n1, k2, n2, k3, n3, k4, n4))
	{
		if (isTetragonRectangle(k1, k2, k3, k4) || isTetragonRectangle(k2, k1, k3, k4) ||
			isTetragonRectangle(k3, k1, k2, k4) || isTetragonRectangle(k4, k1, k2, k3))
		{
			if (areAllSidesEqual(k1, n1, k2, n2, k3, n3, k4, n4) || areAllSidesEqual(k2, n2, k1, n1, k3, n3, k4, n4) ||
				areAllSidesEqual(k3, n3, k1, n1, k2, n2, k4, n4) || areAllSidesEqual(k4, n4, k1, n1, k2, n2, k3, n3))
			{
				cout << "The teragon is a SQUARE!\n";
			}
			else
			{
				cout << "The tetragon is a RECTANGLE!\n";
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
					cout << "The tetragon is a RHOMBUS!\n";
				}
				else
				{
					cout << "The tetragon is a PARALLELOGRAM!\n";
				}
			}
			else if (k1 == k2 || k1 == k3 || 
				k1 == k4 || k2 == k3 || 
				k2 == k4 || k3 == k4)
			{
				cout << "The tetragon is a TRAPEZOID!\n";
			}
			else
			{
				cout << "It is just a tetragon!\n";
			}
		}
	}
}

void usersChoice()
{
	cout << "Enter an option: ";

	string option;
	getline(cin, option);

	convertToLowerCase(option);

	if (option == SAVE_OR_DELETE_CORRESPONDING_NUMBER)
	{
		cout << "\nSave or delete:\n"
			<< "Enter the word \"save\" if you want to save a line or a point\n"
			<< "Enter the word \"delete\" if you want to delete a line or a point\n"
			<< GO_TO_MAIN_MENU_TEXT;
		saveOrDeleteOption();

		//wait();
		showMainMenu();
	}
	else if (option == DEFINE_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nDefine line:\n"
			<< "Enter the word \"slope\" if you want to define a line through slope and a point\n"
			<< "Enter the word \"points\" if you want to define a line through two points\n"
			<< GO_TO_MAIN_MENU_TEXT;
		defineLineOption();

		//wait();
		showMainMenu();
	}
	else if (option == CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nCheck if a point is on a line:\n";
		checkIfPointIsOnLineOption();

		//wait();
		showMainMenu();
	}
	else if (option == FIND_PARALEL_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nFind parallel line:\n";
		findParallelLineOption();

		//wait();
		showMainMenu();
	}
	else if (option == FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nFind perpendicular line:\n";
		findPerpendicularLineOption();

		//wait();
		showMainMenu();
	}
	else if (option == FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER)
	{
		cout << "\nEnter the word \"parabola\" if you want to find the intersection point(s) of a parabola and a line\n"
			<< "Enter the word \"lines\" if you want to find the intersection point(s) of two lines\n"
			<< GO_TO_MAIN_MENU_TEXT;
		findIntersectionPointOption();

		//wait();
		showMainMenu();
	}
	else if (option == FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER)
	{
		cout << "\nFind equations in trinagle by given three points:\n";
		findEquationsInTriangleOption();

		//wait();
		showMainMenu();
	}
	else if (option == FIND_THE_TANGENT_CORRESPONDING_NUMBER)
	{
		cout << "\nFind the tangent of a parabola at a point:\n";
		findTangentOption();

		//wait();
		showMainMenu();
	}
	else if (option == DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER)
	{
		cout << "\nFind the type of tetragon: \n";
		findTheTypeOfTetragonOption();

		//wait();
		showMainMenu();
	}
	else if (option == "exit")
	{
		stopProgram = true;
	}
	else
	{
		cerr << INVALID_INPUT_TEXT;
		usersChoice();
	}
}

int main()
{
	showTitle();
	showMainMenu();

	while (!stopProgram)
	{
		usersChoice();
	}

	//closeAnimation();

	return 0;
}