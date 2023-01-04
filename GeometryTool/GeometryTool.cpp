#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <string.h>
#include <cstring>

using namespace std;
using std::cout;
using std::cin;

const int timeToWait = 1200;

const char* linesDB = "lines.txt";
const char* pointsDB = "points.txt";

const char* SAVE_OR_DELETE_CORRESPONDING_NUMBER = "0";
const char* DEFINE_LINE_CORRESPONDING_NUMBER = "1";
const char* CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER = "2";
const char* FIND_PARALEL_LINE_CORRESPONDING_NUMBER = "3";
const char* FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER = "4";
const char* FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER = "5";
const char* FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER = "6";
const char* FIND_THE_TANGENT_CORRESPONDING_NUMBER = "7";
const char* DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER = "8";

const char* INVALID_INPUT_TEXT = "Invalid input! Try again...\n";
const char* GO_TO_MAIN_MENU_TEXT = "Enter the word \"menu\" if you want to go to the main menu\n";
const char* DATABASE_CANNOT_OPEN_TEXT = "ERROR! We are sorry the database cannot be open!\n";
const char* ENTER_NAME_TEXT = "Enter name (it can be upper and lower case letters, \'_\' and numbers and 16 characters long): \n";
const char* NAME_EXISTS_TEXT = "Name already exists! Try another. . .\n";
const char* NAME_DOESNT_EXIST_TEXT = "Name doesn't exist! Try another. . .\n";
const char* INVALID_NUMBER_TEXT = "Number is too large! It should be between -100 and 100!\n";

bool stopProgram = false;

void wait()
{
	Sleep(timeToWait);
}

bool isNumberValid(const double number)
{
	return abs(number) <= 100;
}

bool areCoordinatesValid(const double x, const double y)
{
	if (!isNumberValid(x))
	{
		cout << "X-coordinate is too large! It should be between -100 and 100!\n";
		return false;
	}

	if (!!isNumberValid(y))
	{
		cout << "Y-coordinate is too large! It should be between -100 and 100!\n";
		return false;
	}

	return true;
}

bool isNameValid(const string name)
{
	if (name.length() > 16)
	{
		cout << "The name is too long! Try again...\n";
		return false;
	}

	for (int i = 0; i < name.length(); i++)
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= '0' && name[i] <= '9')
			|| name[i] == '_'))
		{
			cout << "Invalid characters in name! Try again...\n";
			return false;
		}
	}

	return true;
}

void printLine(const double k, const string symbol, const double n, const double x1 = 101, const double y1 = 101, const double x2 = 102, const double y2 = 102)
{
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
	cin >> keyword;

	cout << "\n";

	convertToLowerCase(keyword);

	return keyword;
}

void printThreeDotsAnimation()
{
	for (int i = 0; i < 3; i++)
	{
		wait();
		cout << ". ";
	}

	wait();
	cout << "\n";
}

void calcAnimation()
{
	cout << "Calculating";
	printThreeDotsAnimation();
}

void loadAnimation()
{
	cout << "Loading";
	printThreeDotsAnimation();
}

void exitAnimation()
{
	cout << "Closing program";
	printThreeDotsAnimation();
}

void saveAnimation()
{
	cout << "Saving";
	printThreeDotsAnimation();
}

void deleteAnimation()
{
	cout << "Deleting";
	printThreeDotsAnimation();
}

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
		<< " " << CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER << " - check if a point is on a line;\n"
		<< " " << FIND_PARALEL_LINE_CORRESPONDING_NUMBER << " - derive an equation of a line that is parallel to a given line and passes through a point;\n"
		<< " " << FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER << " - derive an equation of a perpendicular line to a given line and passes through a point;\n"
		<< " " << FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER << " - find intersection point of two lines (if it exists);\n"
		<< " " << FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER << " - find equations in triangle;\n"
		<< " " << FIND_THE_TANGENT_CORRESPONDING_NUMBER << " - derive an equation of a tangent to a parabola at a corresponding point;\n"
		<< " " << DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER << " - given four equations to determine the type of polygon;\n";
}

string getPoint(const string name)
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
				return words[1];
			}
		}

		database.close();
	}
	else
	{
		cout << DATABASE_CANNOT_OPEN_TEXT;
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
		cout << DATABASE_CANNOT_OPEN_TEXT;
	}

	dataBase.close();
	return false;
}

void saveLine(const string name, const double k, const string symbol, const double n)
{
	ofstream dataBase(linesDB, fstream::app);

	if (dataBase.is_open())
	{
		string data = name + " : " + toString(k) + "*x" + symbol + toString(n);

		dataBase << data << "\n";

		dataBase.close();
	}
	else
	{
		cout << DATABASE_CANNOT_OPEN_TEXT;
	}
}

void saveLineOption(string name = "")
{
	double k, n;
	string symbol;

	if (name == "")
	{
		cout << ENTER_NAME_TEXT;
		cin >> name;
	}

	if (!isNameValid(name))
	{
		saveLineOption();
	}
	else if (isElementInDatabase(name, linesDB))
	{
		cout << NAME_EXISTS_TEXT;
		saveLineOption();
	}
	else
	{
		cout << "Enter the equation of the line using this format \"k*x +/- n\"\n";
		cout << "k: ";
		cin >> k;
		if (isNumberValid(k))
		{
			cout << "\'+\' or \'-\': ";
			cin >> symbol;

			if (symbol != "+" && symbol != "-")
			{
				cout << INVALID_INPUT_TEXT;
				saveLineOption(name);
			}
			else
			{
				cout << "n: ";
				cin >> n;
				if (isNumberValid(n))
				{
					saveLine(name, k, symbol, n);
				}
				else
				{
					cout << INVALID_NUMBER_TEXT;
					saveLineOption(name);
				}
			}
		}
		else
		{
			cout << INVALID_NUMBER_TEXT;
			saveLineOption(name);
		}
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
		cout << DATABASE_CANNOT_OPEN_TEXT;
	}
}

void savePointOption(string name = "")
{
	double x = 0,
		y = 0;

	if (name == "")
	{
		cout << ENTER_NAME_TEXT;
		cin >> name;
	}

	if (!isNameValid(name))
	{
		savePointOption();
	}
	else if (isElementInDatabase(name, pointsDB))
	{
		cout << NAME_EXISTS_TEXT;
		savePointOption();
	}
	else
	{
		cout << "Enter coordinates:\n";
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;
		if (!areCoordinatesValid(x, y))
		{
			savePointOption(name);
		}
		else
		{
			savePoint(name, x, y);
		}
	}
}

void saveOption()
{
	string keyword = getKeywordFromConsole();

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
		cout << INVALID_INPUT_TEXT;
		saveOption();
	}
}

void deleteLine(string name)
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
			cout << "There was an error with the deleting of the line!\nWe are sorry. . .\n";
		}
	}
	else
	{
		cout << DATABASE_CANNOT_OPEN_TEXT;
	}
}

void deleteLineOption()
{
	string name;

	cout << "Enter the name of the line: ";
	cin >> name;

	if (!isElementInDatabase(name, linesDB))
	{
		cout << NAME_DOESNT_EXIST_TEXT;
		deleteLineOption();
	}
	else
	{
		deleteLine(name);
	}
}

void deletePoint(string name)
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
			cout << "There was an error with the deleting of the point!\nWe are sorry. . .\n";
		}
	}
	else
	{
		cout << DATABASE_CANNOT_OPEN_TEXT;
	}
}

void deletePointOption()
{
	string name;

	cout << "Enter the name of the point: ";
	cin >> name;

	if (!isElementInDatabase(name, pointsDB))
	{
		cout << NAME_DOESNT_EXIST_TEXT;
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
		deleteAnimation();
	}
	else if (keyword == "point")
	{
		deletePointOption();
		deleteAnimation();
	}
	else if (keyword != "menu")
	{
		cout << INVALID_INPUT_TEXT;
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
		cout << INVALID_INPUT_TEXT;
		saveOrDeleteOption();
	}
}

void wantToSaveLine(const double k, const string symbol, const double n, string answer = "")
{

	if (answer == "")
	{
		cout << "Do you want to save the line? ";
		cin >> answer;

		convertToLowerCase(answer);
	}

	if (answer == "yes")
	{
		string name;
		cout << ENTER_NAME_TEXT;
		cin >> name;

		if (!isNameValid(name))
		{
			wantToSaveLine(k, symbol, n, answer);
		}
		else if (isElementInDatabase(name, linesDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToSaveLine(k, symbol, n, answer);
		}
		else
		{
			saveLine(name, k, symbol, n);
			saveAnimation();
		}
	}
	else if (answer != "yes" && answer != "no")
	{
		cout << INVALID_INPUT_TEXT;
		wantToSaveLine(k, symbol, n);
	}
}

void wantToSavePoint(const double x, const double y, string answer = "")
{

	if (answer == "")
	{
		cout << "Do you want to save the point? ";
		cin >> answer;

		convertToLowerCase(answer);
	}

	if (answer == "yes")
	{
		string name;
		cout << ENTER_NAME_TEXT;
		cin >> name;

		if (!isNameValid(name))
		{
			wantToSavePoint(x, y, answer);
		}
		else if (isElementInDatabase(name, pointsDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToSavePoint(x, y, answer);
		}
		else
		{
			savePoint(name, x, y);
			saveAnimation();
		}
	}
	else if (answer != "yes" && answer != "no")
	{
		cout << INVALID_INPUT_TEXT;
		wantToSavePoint(x, y);
	}
}

void wantToUseExistingPoint(string& point, string answer = "")
{
	string answer;
	if (answer == "")
	{
		cout << "Do you want to use existing point? ";
		cin >> answer;
	}

	convertToLowerCase(answer);

	if (answer == "yes")
	{
		string name;
		cout << "Enter name: ";
		cin >> name;
		if (isElementInDatabase(name, pointsDB))
		{
			loadAnimation();
			point = getPoint(name);
		}
		else
		{
			cout << NAME_DOESNT_EXIST_TEXT;
			wantToUseExistingPoint(point, answer);
		}
	}
	else if (answer != "no")
	{
		cout << INVALID_INPUT_TEXT;
		wantToUseExistingPoint(point);
	}
}

void defineLineThroughSlopeAndPoint()
{
	double k = 0, x = 0, y = 0;
	string point = "";

	cout << "Enter slope: ";
	cin >> k;

	if (isNumberValid(k))
	{
		wantToUseExistingPoint(point);

		if (point == "")
		{
			cout << "Enter coordinates of the point:\nx: ";
			cin >> x;
			cout << "y: ";
			cin >> y;

			wantToSavePoint(x, y);
		}
		else
		{
			vector<string> coordinates;
			splitByDelim(coordinates, point, ";");

			x = stod(coordinates[0]);
			y = stod(coordinates[1]);
		}

		if (!areCoordinatesValid(x, y))
		{
			defineLineThroughSlopeAndPoint();
		}
		else
		{
			double n = k * x - y;
			string symbol = n >= 0 ? "+" : "-";
			n = abs(n);

			calcAnimation();
			printLine(k, symbol, n);

			wantToSaveLine(k, symbol, n);
		}
	}
	else
	{
		cout << INVALID_NUMBER_TEXT;
		defineLineThroughSlopeAndPoint();
	}
}

void defineLineThroughPoints()
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	string point1 = "";
	wantToUseExistingPoint(point1);

	if (point1 == "")
	{
		cout << "Enter coordinates of the point:\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;

		wantToSavePoint(x1, y1);
	}
	else
	{
		vector<string> coordinates;
		splitByDelim(coordinates, point1, ";");

		x1 = stod(coordinates[0]);
		y1 = stod(coordinates[1]);
	}
	if (!areCoordinatesValid(x1, y1))
	{
		defineLineThroughPoints();
	}
	else
	{
		string point2 = "";
		wantToUseExistingPoint(point2);

		if (point2 == "")
		{
			cout << "Enter coordinates of the point:\nx: ";
			cin >> x2;
			cout << "y: ";
			cin >> y2;

			wantToSavePoint(x2, y2);
		}
		else
		{
			vector<string> coordinates{};
			splitByDelim(coordinates, point2, ";");

			x2 = stod(coordinates[0]);
			y2 = stod(coordinates[1]);
		}
		if (!areCoordinatesValid(x2, y2))
		{
			defineLineThroughPoints();
		}
		else
		{
			if (x1 == x2 && y1 == y2)
			{
				cout << "Can't define a line! Points are the same!\n";
			}
			else
			{
				if (x1 == x2)
				{
					double k = 1;
					double n = -x1;
					string symbol = n >= 0 ? "+" : "-";

					calcAnimation();
					printLine(k, symbol, n, x1, y1, x2, y2);

					cout << "The program cannot save lines that has equal x-coordinates! We're sorry...";
				}
				else if (y1 == y2)
				{
					double k = 0;
					double n = -y1;
					string symbol = n >= 0 ? "+" : "-";

					calcAnimation();
					printLine(k, symbol, n, x1, y1, x2, y2);

					cout << "The program cannot save lines that has equal y-coordinates! We're sorry...";
				}
				else
				{
					double k = (y1 - y2) / (x1 - x2);
					double n = k * x1 - y1;
					string symbol = n >= 0 ? "+" : "-";
					n = abs(n);

					calcAnimation();
					printLine(k, symbol, n, x1, y1, x2, y2);

					wantToSaveLine(k, symbol, n);
				}
			}
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
		cout << INVALID_INPUT_TEXT;
		defineLineOption();
	}
}

void checkIfDotIsOnLineOption()
{

}

void usersChoice()
{
	cout << "Enter an option: ";

	string option;
	cin >> option;

	convertToLowerCase(option);

	if (option == SAVE_OR_DELETE_CORRESPONDING_NUMBER)
	{
		cout << "\nEnter the word \"save\" if you want to save a line or a point\n"
			<< "Enter the word \"delete\" if you want to delete a line or a point\n"
			<< GO_TO_MAIN_MENU_TEXT;

		saveOrDeleteOption();

		wait();
		showMainMenu();
	}
	else if (option == DEFINE_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nEnter the word \"slope\" if you want to define a line through slope and a point\n"
			<< "Enter the word \"points\" if you want to define a line through two points\n"
			<< GO_TO_MAIN_MENU_TEXT;

		defineLineOption();

		wait();
		showMainMenu();
	}
	else if (option == CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER)
	{
		checkIfDotIsOnLineOption();

		wait();
		showMainMenu();
	}
	else if (option == FIND_PARALEL_LINE_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == FIND_THE_TANGENT_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER)
	{

		wait();
		showMainMenu();
	}
	else if (option == "exit")
	{
		stopProgram = true;
	}
	else
	{
		cout << INVALID_INPUT_TEXT;
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

	exitAnimation();

	return 0;
}