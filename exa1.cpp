#include <iostream>
#include "FormInterpreter.h"

int main()
{
  formInterpreter MyFormula("2*3", formInterpreter::isRad, 0., true);
  double result = MyFormula.calc();
  std::cout << "Result = " << result << std::endl;

  return 0;
}
