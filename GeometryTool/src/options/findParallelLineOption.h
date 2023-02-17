#pragma once

void findParallelLineOption()
{
	double k, n;

	getLineArguments(k, n);

	double x, y;

	getPointCoordinates(x, y);

	n = k * x - y;

	calcAnimation();
	printLine(k, n, x, y);

	wantToSaveLine(k, n);
}
