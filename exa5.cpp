#include <iostream>
#include "FormInterpreter.h"
//-------------------------------------------------------------
double _Formula_AreaRectangle(double width, double height) {
  return (width * height);
}
//-------------------------------------------------------------
int main()
{
  formInterpreter Function("2 * AREA(5., 6.)");
  Function.addFunction("AREA", _Formula_AreaRectangle, 1, 1, 0);
  std::cout << "2 * AREA = " << Function.calc() << std::endl;
  return 0;
}
