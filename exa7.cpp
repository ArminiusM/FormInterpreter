#include <iostream>
#include "FormInterpreter.h"
//-------------------------------------------------------------
int main()
{
  formInterpreter Function("4 + 5 - 2 * 10 / 5", formInterpreter::isDegree, 0., true);
  std::cout << "Result = " << Function.calc() << std::endl;
  return 0;
}
