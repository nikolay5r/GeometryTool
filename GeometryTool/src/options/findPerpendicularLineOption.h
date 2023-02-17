#pragma once

void findPerpendicularLineOption()
{
	double k, n;

	getLineArguments(k, n);

	double x, y;

	getPointCoordinates(x, y);

	calculatePerpendicularLineArgs(k, n, x, y);

	calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}
