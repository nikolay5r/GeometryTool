#pragma once
#include <string>

bool isInputNumber(std::string input);
bool isNumberValid(const double number);
bool areLinesTheSame(double k1, double n1, double k2, double n2);
bool isNameValid(const std::string name);
bool arePointsTheSame(double& x1, double& y1, double& x2, double& y2);
bool arePointsOnTheSameLine(double x1, double y1, double x2, double y2, double x3, double y3);
bool checkIfTetragonCanBeCreated(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4);
bool areLinesPerpendicular(double k1, double k2);
bool isTetragonRectangle(double k1, double k2, double k3, double k4);
bool areAllSidesEqual(double k1, double n1, double k2, double n2, double k3, double n3, double k4, double n4);
bool isElementInDatabase(const std::string element, const char* path);