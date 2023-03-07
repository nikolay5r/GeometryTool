
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <string.h>
#include <string>
#include <windows.h>

bool stopProgram = false;

#include "src/print.h"
#include "src/animation.h"
#include "src/helper.h"
#include "src/validation.h"
#include "src/services/pointService.h"
#include "src/services/lineService.h"
#include "src/userInteraction.h"
#include "src/options/saveAndDeleteOption.h"
#include "src/options/defineLineOption.h"
#include "src/options/checkIfPointIsOnLineOption.h"
#include "src/options/findParallelLineOption.h"
#include "src/options/findPerpendicularLineOption.h"
#include "src/options/findIntersectionPointOption.h"
#include "src/options/findTangentOption.h"
#include "src/options/findEquationsInTriangle.h"
#include "src/options/determineTheTypeOfTetragonOption.h"

void usersChoice()
{
	std::cout << "Enter an option: ";

	std::string option;
	std::getline(std::cin, option);

	convertToLowerCase(option);

	if (option == SAVE_OR_DELETE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nSave or delete:\n"
			<< "Enter the word \"save\" if you want to save a line or a point\n"
			<< "Enter the word \"delete\" if you want to delete a line or a point\n"
			<< GO_TO_MAIN_MENU_TEXT;
		saveOrDeleteOption();

		wait();
		printMainMenu();
	}
	else if (option == DEFINE_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nDefine line:\n"
			<< "Enter the word \"slope\" if you want to define a line through slope and a point\n"
			<< "Enter the word \"points\" if you want to define a line through two points\n"
			<< GO_TO_MAIN_MENU_TEXT;
		defineLineOption();

		wait();
		printMainMenu();
	}
	else if (option == CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nCheck if a point is on a line:\n";
		checkIfPointIsOnLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_PARALEL_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind parallel line:\n";
		findParallelLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind perpendicular line:\n";
		findPerpendicularLineOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER)
	{
		std::cout << "\nEnter the word \"parabola\" if you want to find the intersection point(s) of a parabola and a line\n"
			<< "Enter the word \"lines\" if you want to find the intersection point(s) of two lines\n"
			<< GO_TO_MAIN_MENU_TEXT;
		findIntersectionPointOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind equations in trinagle by given three points:\n";
		findEquationsInTriangleOption();

		wait();
		printMainMenu();
	}
	else if (option == FIND_THE_TANGENT_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind the tangent of a parabola at a point:\n";
		findTangentOption();

		wait();
		printMainMenu();
	}
	else if (option == DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER)
	{
		std::cout << "\nFind the type of tetragon: \n";
		determineTheTypeOfTetragonOption();

		wait();
		printMainMenu();
	}
	else if (option == "exit")
	{
		stopProgram = true;
	}
	else
	{
		std::cerr << INVALID_INPUT_TEXT;
		usersChoice();
	}
}

int main()
{
	printTitle();
	printMainMenu();

	while (!stopProgram)
	{
		usersChoice();
	}

	closeAnimation();

	return 0;
}
