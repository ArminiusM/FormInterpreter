#include <iostream>
#include "FormInterpreter.h"

int main()
{
  formInterpreter xFunction("radius * COS(x)",
                             formInterpreter::isDegree);
  formInterpreter yFunction("radius * SIN(x)",
                             formInterpreter::isDegree);
  xFunction.defineVariable("radius", 2.);
  yFunction.defineVariable("radius", 2.);
  for (int i=0; i<=360; i++) {
    double x = xFunction.calc((double)i);
    double y = yFunction.calc((double)i);
    std::cout << "x = " << x << " y = " << y << std::endl;
  }
  return 0;
}
