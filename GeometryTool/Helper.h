#pragma once
#include <iostream>
#include <vector>

std::string calculateLineByTwoPoints(double& k, double& n, double x1, double y1, double x2, double y2);
void splitByDelim(std::vector<std::string>& words, std::string text, std::string delim = " ");
void convertToLowerCase(std::string& text);
void calculatePerpendicularLineArgs(double& k, double& n, double& x, double& y);
void calculateIntersectionPointOfTwoLines(double& x, double& y, double k1, double n1, double k2, double n2);
void calculateHeights(double xa, double ya, double xb, double yb, double xc, double yc);
void calculateMedians(double xa, double ya, double xb, double yb, double xc, double yc);
void calculateSemetrals(double xa, double ya, double xb, double yb, double xc, double yc);
std::string toString(double number);