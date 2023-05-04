#pragma once
#include <iostream>

void getN(double& n);
void getSlope(double& k);
std::string getKeywordFromConsole();
void getXCoord(double& x);
void getYCoord(double& y);
void setEquationOfLine(double& k, double& n);
void setPointCoordinates(double& x, double& y);
void getAnswer(std::string& answer, std::string question);
void getName(std::string& name);
void wantToSavePoint(const double x, const double y, std::string answer = "");
void wantToSaveLine(const double k, const double n, std::string answer = "");
void wantToUseExistingPoint(std::string& point, std::string answer = "");
void wantToUseExistingLine(std::string& line, std::string answer = "");
void getCoordinatesFromExistingPoint(std::string point, double& x, double& y);
void getArgumentsFromExistingLine(std::string equation, double& k, double& n);
void getLineArguments(double& k, double& n);
void getPointCoordinates(double& x, double& y);
void getParabola(double& p);