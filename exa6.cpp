#include <iostream>
#include "FormInterpreter.h"
//-------------------------------------------------------------
double _Formula_sum(double a, double b, double c, double d) {
  return a+b+c+d;
}
//-------------------------------------------------------------
int main()
{
  formInterpreter Function("SUM(1., 2., 3., 4.)");
  Function.addFunction("SUM", _Formula_sum, 1, 1, 0);
  std::cout << "SUM = " << Function.calc() << std::endl;
  return 0;
}
