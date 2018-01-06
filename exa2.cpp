#include <iostream>
#include "FormInterpreter.h"

int main()
{
  formInterpreter MyFormula("x^2");
  for (int i=1; i<=3; i++) {
    double result = MyFormula.calc((double)i);
    std::cout << "x = " << i << " Result = " << result << std::endl;
  }

  return 0;
}
