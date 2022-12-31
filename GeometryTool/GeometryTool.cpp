#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

const string SAVE_OR_DELETE_CORRESPONDING_NUMBER = "0";
const string DEFINE_LINE_CORRESPONDING_NUMBER = "1";
const string CHECK_IF_DOT_IS_ON_LINE_CORRESPONDING_NUMBER = "2";
const string FIND_PARALEL_LINE_CORRESPONDING_NUMBER = "3";
const string FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER = "4";
const string FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER = "5";
const string FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER = "6";
const string FIND_THE_TANGENT_CORRESPONDING_NUMBER = "7";
const string DETERMINE_THE_TYPE_OF_POLYGON_CORRESPONDING_NUMBER = "8";

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

int main()
{

}