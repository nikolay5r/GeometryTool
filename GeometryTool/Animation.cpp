#include <windows.h>
#include <iostream>

#include "Constants.h"

void wait()
{
	Sleep(constants::TIME_TO_SLEEP);
}

void printThreeDotsAnimation()
{
	for (int i = 0; i < 3; i++)
	{
		wait();
		std::cout << ". ";
	}

	wait();
	std::cout << "\n";
}

void calcAnimation()
{
	std::cout << "Calculating";
	printThreeDotsAnimation();
}

void loadAnimation()
{
	std::cout << "Loading";
	printThreeDotsAnimation();
}

void closeAnimation()
{
	std::cout << "Closing program";
	printThreeDotsAnimation();
}

void saveAnimation()
{
	std::cout << "Saving";
	printThreeDotsAnimation();
}

void deleteAnimation()
{
	std::cout << "Deleting";
	printThreeDotsAnimation();
}

