#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

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
const char* ENTER_NAME_TEXT = "Enter name (it can be upper and lower case letters, \'_\' and numbers): ";
const char* NAME_EXISTS_TEXT = "That name already exists! Try another. . .\n";

bool stopProgram = false;

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
		Sleep(1200);
		cout << ". ";
	}

	Sleep(1200);
	cout << "\n";
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

	if (text.find(delim) == string::npos)
	{
		words.push_back(text);
	}
	
	while ((pos = text.find(delim)) != string::npos) {
		words.push_back(text.substr(0, pos));
		text.erase(0, pos + delim.length());
	}
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

bool isElementInDatabase(string element, const char* path)
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
				return true;
			}
		}

		dataBase.close();

		return false;
	}
	else
	{
		cout << DATABASE_CANNOT_OPEN_TEXT;
		showMainMenu();
	}
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
		showMainMenu();
	}
}

void saveLineOption()
{
	string name;
	double k, n;
	string symbol;

	cout << ENTER_NAME_TEXT;
	cin >> name;

	if (isElementInDatabase(name, linesDB))
	{
		cout << NAME_EXISTS_TEXT;
		saveLineOption();
	}
	else
	{
		cout << "Enter the equation of the line using this format \"k*x +/- n\"\n";
		cout << "k: ";
		cin >> k;
		cout << "\'+\' or \'-\': ";
		cin >> symbol;
		if (symbol != "+" && symbol != "-")
		{
			cout << INVALID_INPUT_TEXT;
			saveLineOption();
		}
		else
		{
			cout << "n: ";
			cin >> n;
			saveLine(name, k, symbol, n);
		}
	}
}

void savePoint(string name, double x, double y)
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
		showMainMenu();
	}
}

void savePointOption()
{
	string name = "";
	double x = 0,
		y = 0;

	cout << ENTER_NAME_TEXT;
	cin >> name;

	if (isElementInDatabase(name, pointsDB))
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

		savePoint(name, x, y);
	}
}

void saveOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		saveLineOption();
		saveAnimation();
		showMainMenu();
	}
	else if (keyword == "point")
	{
		savePointOption();
		saveAnimation();
		showMainMenu();
	}
	else if (keyword == "menu")
	{
		showMainMenu();
	}
	else
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
		showMainMenu();
	}
}

void deleteLineOption()
{
	string name;

	cout << "Enter the name of the line: ";
	cin >> name;

	if (!isElementInDatabase(name, linesDB))
	{
		cout << "That name doesn't exist! Try another. . .\n";
		deleteLineOption();
	}

	deleteLine(name);
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
		showMainMenu();
	}
}

void deletePointOption()
{
	string name;

	cout << "Enter the name of the point: ";
	cin >> name;

	if (!isElementInDatabase(name, pointsDB))
	{
		cout << "That name doesn't exist! Try another. . .\n";
		deletePointOption();
	}

	deletePoint(name);
}

void deleteOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
		deleteLineOption();
		deleteAnimation();
		showMainMenu();
	}
	else if (keyword == "point")
	{
		deletePointOption();
		deleteAnimation();
		showMainMenu();
	}
	else if (keyword == "menu")
	{
		showMainMenu();
	}
	else
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
	else if (keyword == "menu")
	{
		showMainMenu();
	}
	else
	{
		cout << INVALID_INPUT_TEXT;
		saveOrDeleteOption();
	}
}

void wantToSaveLine(const double k, const string symbol, const double n)
{
	string answer;
	cout << "Do you want to save the line? ";
	cin >> answer;

	if (answer == "yes")
	{
		string name;
		cout << ENTER_NAME_TEXT;
		cin >> name;
		if (isElementInDatabase(name, linesDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToSaveLine(k, symbol, n);
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

void wantToSavePoint(const double x, const double y)
{
	string answer;
	cout << "Do you want to save the point? ";
	cin >> answer;

	if (answer == "yes")
	{
		string name;
		cout << ENTER_NAME_TEXT;
		cin >> name;
		if (isElementInDatabase(name, pointsDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToSavePoint(x, y);
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

void wantToUseExistingPoint()
{
	string answer;
	cout << "Do you want to use existing point? (yes/no) - ";
	cin >> answer;

	if (answer == "yes")
	{
		string name;
		cout << ENTER_NAME_TEXT;
		cin >> name;
		if (isElementInDatabase(name, pointsDB))
		{
			cout << NAME_EXISTS_TEXT;
			wantToUseExistingPoint();
		}
		else
		{
			
		}
	}
	else if (answer != "yes" && answer != "no")
	{

	}
}

void defineLineThroughSlope()
{
	double k, x, y;

	cout << "Enter slope: ";
	cin >> k;

	

	cout << "Enter coordinates of the point:\nx: ";
	cin >> x;
	cout << "y: ";
	cin >> y;

	wantToSavePoint(x, y);
	
	double n = k * x - y;
	string symbol = n >= 0 ? "+" : "-";
	n = abs(n);

	if (n == 0)
	{
		cout << "The equation of the line is: y = " << k << " * x\n";
	}
	else
	{
		cout << "The equation of the line is: y = " << k << " * x " << symbol << " " << n << "\n";
	}

	wantToSaveLine(k, symbol, n);
}

void defineLineOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "slope")
	{
		defineLineThroughSlope();
		showMainMenu();
	}
	else if (keyword == "points")
	{

	}
	else if (keyword == "menu")
	{
		showMainMenu();
	}
	else
	{
		cout << INVALID_INPUT_TEXT;
		defineLineOption();
	}
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
	}
	else if (option == DEFINE_LINE_CORRESPONDING_NUMBER)
	{
		cout << "\nEnter the word \"slope\" if you want to define a line through slope and a point\n"
			<< "Enter the word \"points\" if you want to define a line through two points\n"
			<< GO_TO_MAIN_MENU_TEXT;

		defineLineOption();
	}
	else if (option == CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER)
	{

	}
	else if (option == FIND_PARALEL_LINE_CORRESPONDING_NUMBER)
	{

	}
	else if (option == FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER)
	{

	}
	else if (option == FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER)
	{

	}
	else if (option == FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER)
	{

	}
	else if (option == FIND_THE_TANGENT_CORRESPONDING_NUMBER)
	{

	}
	else if (option == DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER)
	{

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