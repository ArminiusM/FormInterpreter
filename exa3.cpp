#include <iostream>
#include "FormInterpreter.h"

int main()
{
  formInterpreter MyFormula("radius * COS(angle)",
                            formInterpreter::isDegree);
  MyFormula.defineVariable("radius", 2.);
  MyFormula.defineVariable("angle", 45.);
  double result = MyFormula.calc();
  std::cout << "Result = " << result << std::endl;

  return 0;
}
