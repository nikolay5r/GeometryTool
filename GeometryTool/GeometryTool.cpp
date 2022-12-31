#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

const string linesDB = "lines.txt";
const string pointsDB = "points.txt";

const string SAVE_OR_DELETE_CORRESPONDING_NUMBER = "0";
const string DEFINE_LINE_CORRESPONDING_NUMBER = "1";
const string CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER = "2";
const string FIND_PARALEL_LINE_CORRESPONDING_NUMBER = "3";
const string FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER = "4";
const string FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER = "5";
const string FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER = "6";
const string FIND_THE_TANGENT_CORRESPONDING_NUMBER = "7";
const string DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER = "8";

const string INVALID_INPUT_TEXT = "Invalid input! Try again...\n";
const string GO_TO_MAIN_MENU_TEXT = "Enter the word \"menu\" if you want to go to the main menu\n";

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

string getKeywordFromConsole()
{
	cout << "Keyword: ";

	string keyword = "";
	cin >> keyword;

	cout << "\n";

	convertToLowerCase(keyword);

	return keyword;
}

void showTitle()
{
	cout << "\n\t\t\t---GeometryTool---\n";
}

void showMainMenu()
{
	cout << "\nEnter a number corresponding to the option you want to choose or enter \"exit\" if you want to exit:\n";

	cout << " " << SAVE_OR_DELETE_CORRESPONDING_NUMBER << " - save a line or a point or delete one;\n"
		<< " " << DEFINE_LINE_CORRESPONDING_NUMBER << " - define a line through coefficient and points;\n"
		<< " " << CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER << " - check if a point is on a line;\n"
		<< " " << FIND_PARALEL_LINE_CORRESPONDING_NUMBER << " - derive an equation of a line that is parallel to a given line (g) and\n     passes through a point (p) from the given line;\n"
		<< " " << FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER << " - derive an equation of a perpendicular line to a given line (g) and\n     passes through a point (p) from the given line;\n"
		<< " " << FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER << " - find intersection point of two lines (if it exists);\n"
		<< " " << FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER << " - find equations in triangle;\n"
		<< " " << FIND_THE_TANGENT_CORRESPONDING_NUMBER << " - derive an equation of a tangent to the parabola at a corresponding point;\n"
		<< " " << DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER << " - given four equations to determine the type of polygon;\n";
}

void saveLineOption()
{
	string name;
	double k, n;
	string symbol;

	cout << "Enter name of a line (it can be upper and lower case letters, \'_\' and numbers): ";
	cin >> name;
		cout << "Enter the equation of the line using this format \"k*x +/- n\"\n";
		cout << "k: ";
		cin >> k;
		cout << "\'+\' or \'-\': ";
		cin >> symbol;
			cout << "n: ";
			cin >> n;

}

void saveOption()
{
	string keyword = getKeywordFromConsole();

	if (keyword == "line")
	{
	}
	else if (keyword == "point")
	{
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

	return 0;
}