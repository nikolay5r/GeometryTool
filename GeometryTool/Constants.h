#pragma once

namespace constants
{
	const int TIME_TO_SLEEP = 1200;
	const int MAX_NAME_LENGTH = 16;
	const int MAX_NUMBER_SIZE = 100;

	const char SAVE_OR_DELETE_CORRESPONDING_NUMBER[] = "0";
	const char DEFINE_LINE_CORRESPONDING_NUMBER[] = "1";
	const char CHECK_IF_POINT_IS_ON_LINE_CORRESPONDING_NUMBER[] = "2";
	const char FIND_PARALEL_LINE_CORRESPONDING_NUMBER[] = "3";
	const char FIND_PERPENDICULAR_LINE_CORRESPONDING_NUMBER[] = "4";
	const char FIND_INTERSECTION_POINT_CORRESPONDING_NUMBER[] = "5";
	const char FIND_EQUATIONS_IN_TRIANGLE_CORRESPONDING_NUMBER[] = "6";
	const char FIND_THE_TANGENT_CORRESPONDING_NUMBER[] = "7";
	const char DETERMINE_THE_TYPE_OF_TETRAGON_CORRESPONDING_NUMBER[] = "8";

	const char INVALID_INPUT_TEXT[] = "Invalid input! Try again...\n";
	const char GO_TO_MAIN_MENU_TEXT[] = "Enter the word \"menu\" if you want to go to the main menu\n";
	const char DATABASE_CANNOT_OPEN_TEXT[] = "ERROR! We are sorry the database cannot be opened!\n";
	const char ENTER_NAME_TEXT[] = "Enter name (it can be upper and lower case letters, \'_\' and numbers and 16 characters long): \n";
	const char NAME_EXISTS_TEXT[] = "Name already exists! Try another. . .\n";
	const char NAME_DOESNT_EXIST_TEXT[] = "Name doesn't exist! Try another. . .\n";
	const char INVALID_NUMBER_TEXT[] = "Number is too large! It should be between -100 and 100!\n";

	const char linesDB[] = "data/lines.txt";
	const char pointsDB[] = "data/points.txt";
}