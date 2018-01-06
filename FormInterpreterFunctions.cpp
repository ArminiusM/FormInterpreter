//-------------------------------------------------------------------------------------
#include "FormInterpreterFunctions.h"
#include "math.h"
//-------------------------------------------------------------------------------------
double _FormInterpreter_Random(double argument) {
  return (double)(rand() % (int)(argument+.5));
}
//-------------------------------------------------------------------------------------
double _FormInterpreter_AreaRectangle(double width, double height) {
  return width * height;
}
//-------------------------------------------------------------------------------------
double _FormInterpreter_AreaCubic(std::vector<double> parameters) {
  if (parameters.size() != 3) throw FormulaException(100, "AreaCubic: Three parameters needed");
  return parameters.at(0) * parameters.at(1) * parameters.at(2);
}
//-------------------------------------------------------------------------------------
double _FormInterpreter_GeoStat(double mE, double omega) {
  double Pi = 4 * atan(1.);
  return pow(6.67259E-11 * mE * omega * omega / (4. * Pi * Pi), 1./3.);
}
//-------------------------------------------------------------------------------------
double _FormInterpreter_Sum(std::vector<double> parameters) {
  double result = 0.;
  for (unsigned int i=0; i<parameters.size(); i++) {
    result += parameters.at(i);
  }
  return result;
}
//-------------------------------------------------------------------------------------
double _FormInterpreter_Half(std::vector<double> parameters) {
  if (parameters.size() != 1) throw FormulaException(100, "Half: One parameter needed");
  return parameters.at(0) / 2.;
}
//-------------------------------------------------------------------------------------
