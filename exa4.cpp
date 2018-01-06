#include <iostream>
#include "FormInterpreter.h"

int main()
{
  formInterpreter xFunction("radius * COS(angle)",
                             formInterpreter::isDegree);
  formInterpreter yFunction("radius * SIN(angle)",
                             formInterpreter::isDegree);
  xFunction.defineVariable("radius", 2.);
  yFunction.defineVariable("radius", 2.);
  for (int i=0; i<=360; i++) {
    xFunction.defineVariable("angle", (double)i);
    yFunction.defineVariable("angle", (double)i);
    double x = xFunction.calc();
    double y = yFunction.calc();
    std::cout << "x = " << x << " y = " << y << std::endl;
  }
  return 0;
}
