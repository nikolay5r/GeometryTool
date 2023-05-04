#pragma once
#include <iostream>

void savePoint(const std::string name, const double x, const double y);
void deletePoint(const std::string name);
void getPoint(const std::string name, std::string& point);
