//-------------------------------------------------------------------------------------
#ifndef FormInterpreter_CUSTOM_FUNCTIONS_H
#define FormInterpreter_CUSTOM_FUNCTIONS_H

#include <cstdlib>
#include <vector>
#include "FormInterpreter.h"

double _FormInterpreter_Random(double argument);
double _FormInterpreter_AreaRectangle(double width, double height);
double _FormInterpreter_AreaCubic(std::vector<double> parameters);
double _FormInterpreter_GeoStat(double Me, double omega);
double _FormInterpreter_Sum(std::vector<double> parameters);
double _FormInterpreter_Half(std::vector<double> parameters);

#endif
