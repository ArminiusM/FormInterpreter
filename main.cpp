#include <iostream>
#include <vector>
#include "FormInterpreterFunctions.h"
#include "FormInterpreter.h"

struct s_variable {
  std::string name;
  double value;
};


int testFormula(std::string form, double expected, std::vector<s_variable> customVars, std::vector<c_function> customFunctions);
int testFormula(std::string form, double x, double expected, std::vector<s_variable> customVars, std::vector<c_function> customFunctions);

int main()
{
  std::vector<s_variable> customVars;
  std::vector<c_function> customFunctions;
  double expected;
  int errors = 0;

  expected = floor(1.5);
  errors += testFormula("FLOOR(1.5)", expected, customVars, customFunctions);

  expected = floor(-1.5);
  errors += testFormula("FLOOR(-1.5)", expected, customVars, customFunctions);

  expected = 5 + 2 * 4;
  errors += testFormula("5 + 2 * 4", expected, customVars, customFunctions);

  expected = -5 + 2 * 4;
  errors += testFormula("-5 + 2 * 4", expected, customVars, customFunctions);

  expected = 5 * 3 + 8 / 4;
  errors += testFormula("5 * 3 + 8 / 4", expected, customVars, customFunctions);

  expected = 6*(8-5)+4;
  errors += testFormula("6 * (8 - 5) + 4", expected, customVars, customFunctions);

  expected = 6*4-(9-2);
  errors += testFormula("6 * 4 - (9 - 2)", expected, customVars, customFunctions);

  expected = 1 + 2 * 3 * 4;
  errors += testFormula("1 + 2 * 3 * 4", expected, customVars, customFunctions);

  expected = (1 + 2) * (3 + 4);
  errors += testFormula("(1 + 2) * (3 + 4)", expected, customVars, customFunctions);

  expected = 1 + 2 * 3 + 4;
  errors += testFormula("1 + 2 * 3 + 4", expected, customVars, customFunctions);

  expected = (1 + 2) * -(3 + 4);
  errors += testFormula("(1 + 2) * -(3 + 4)", expected, customVars, customFunctions);

  expected = 1 + 2 * 3 + 4;
  errors += testFormula("1 + 2 * 3 + 4", expected, customVars, customFunctions);

  expected = 1 + -(-1);
  errors += testFormula("1 + -(-1)", expected, customVars, customFunctions);

  expected = 1 + +(-1);
  errors += testFormula("1 + +-1", expected, customVars, customFunctions);

  expected = 1 + +(+1);
  errors += testFormula("1 + ++1", expected, customVars, customFunctions);

  expected = (23-4*2)/3;
  errors += testFormula("(23 - 4 * 2) / 3", expected, customVars, customFunctions);

  expected = -(23-4*2);
  errors += testFormula("-(23 - 4 * 2)", expected, customVars, customFunctions);

  expected = 2+16/4*3-13;
  errors += testFormula("2 + 16 / 4 * 3 - 13", expected, customVars, customFunctions);

  expected = 18-7*2+12/4;
  errors += testFormula("18 - 7 * 2+12 / 4", expected, customVars, customFunctions);

  expected = 5*2+15/3-9;
  errors += testFormula("5 * 2 + 15 / 3 - 9", expected, customVars, customFunctions);

  expected = 10/5+3*6-16;
  errors += testFormula("10 / 5 + 3 * 6 - 16", expected, customVars, customFunctions);

  expected = 5+10-6.*3./-2.;
  errors += testFormula("5 + 10 - 6. * 3. / -2.", expected, customVars, customFunctions);

  expected = 18-13+10*2/4;
  errors += testFormula("18 - 13 + 10 * 2. / 4.", expected, customVars, customFunctions);

  expected = 2*5+6-10./4.;
  errors += testFormula("2 * 5 + 6 - 10. / 4.", expected, customVars, customFunctions);

  expected = 14/7+16-8*2;
  errors += testFormula("14 / 7+ 16- 8 * 2", expected, customVars, customFunctions);

  expected = 2 * cos(45*M_PI/180.);
  errors += testFormula("2 * COS(45.*Pi/180.)", expected, customVars, customFunctions);

  expected = 2 * M_PI;
  errors += testFormula("2*Pi", expected, customVars, customFunctions);

  expected = 2 * 3 / 2;
  errors += testFormula("2 * 3 / 2", expected, customVars, customFunctions);

  expected = 2*3+pow(M_PI,4);
  errors += testFormula("2*3+Pi^4", expected, customVars, customFunctions);

  expected = 6. / (3 * 2);
  errors += testFormula("6. / (3 * 2)", expected, customVars, customFunctions);

  expected = 6. / 3 * 2;
  errors += testFormula("6. / 3 * 2", expected, customVars, customFunctions);

  expected = 6. / (3 * 2 * (4 + 2));
  errors += testFormula("6. / (3 * 2 * (4 + 2))", expected, customVars, customFunctions);

  expected = 6. / (-(3 + 2) * (4 + 2) + 5);
  errors += testFormula("6. / (-(3 + 2) * (4 + 2) + 5)", expected, customVars, customFunctions);

  expected = 2 + pow(2,2) * 2;
  errors += testFormula("2 + 2^2 * 2", expected, customVars, customFunctions);

  expected = 2.7182818284;
  errors += testFormula("Euler", expected, customVars, customFunctions);

  expected = 1+2*pow(3,4);
  errors += testFormula("1+2*3^4", expected, customVars, customFunctions);

  expected = 1+2*pow(3,4)+2;
  errors += testFormula("1+2*3^4+2", expected, customVars, customFunctions);

  expected = pow(2,3)*4+5;
  errors += testFormula("2^3*4+5", expected, customVars, customFunctions);

  expected = 1+2*pow(3,(4+2));
  errors += testFormula("1+2*3^(4+2)", expected, customVars, customFunctions);

  expected = 2*pow(pow(2,3), 4)*4+5;
  errors += testFormula("2*2^3^4*4+5", expected, customVars, customFunctions);

  expected = 3. + 5. * 3. + pow(2.,2.) * 4. + 3. / 2. + 3. - 2. * 2.;
  errors += testFormula("3 + 5 * 3 + 2 ^ 2 * 4 + 3 / 2 + 3 - 2 * 2", expected, customVars, customFunctions);

  expected = 3. + 5. * 3. + pow(2.,2.) * pow(4., 2.) + 3. / 2. + 3. - 2. * 2.;
  errors += testFormula("3 + 5 * 3 + 2 ^ 2 * 4^2 + 3 / 2 + 3 - 2 * 2", expected, customVars, customFunctions);

  expected = 3. + 5. * 3. + pow(2.,-(2.+ -2)) * pow(4., 2.) + 3. / 2. + 3. - 2. * 2.;
  errors += testFormula("3 + 5 * 3 + 2 ^ -(2+-2) * 4^2 + 3 / 2 + 3 - 2 * 2", expected, customVars, customFunctions);

  expected = 6 * 3 - 2 * 4;
  errors += testFormula("6 * 3 - 2 * 4", expected, customVars, customFunctions);

  expected = 6 * 3 + sqrt(3*8-2*4) * 2 / 4 + 6 - 1 + 2 * 4 -3;
  errors += testFormula("6 * 3 + SQRT(3*8-2*4) * 2 / 4 + 6 - 1 + 2 * 4 -3", expected, customVars, customFunctions);

  expected = 6 * (3 - 2) * 4;
  errors += testFormula("6 * (3 - 2) * 4", expected, customVars, customFunctions);

  expected = 6 * ((3 - 2) * 4 + 2);
  errors += testFormula("6 * ((3 - 2) * 4 + 2)", expected, customVars, customFunctions);

  expected = 5 - -3;
  errors += testFormula("5 -  -3", expected, customVars, customFunctions);

  expected = 8. * atan(1);
  errors += testFormula("2 * Pi", expected, customVars, customFunctions);

  expected = sin(0);
  errors += testFormula("SIN(0)", expected, customVars, customFunctions);

  expected = 45;
  errors += testFormula("ATAN(1) * 180/Pi", expected, customVars, customFunctions);

  expected = 45;
  errors += testFormula("ATAN2(1,1) * 180/Pi", expected, customVars, customFunctions);

  s_variable customVar;
  customVars.clear();
  customVar.name = "Length";
  customVar.value = 45.;
  customVars.push_back(customVar);
  customVar.name = "Width";
  customVar.value = 3.;
  customVars.push_back(customVar);
  expected = 45. * 3.;
  errors += testFormula("Length * Width", expected, customVars, customFunctions);

  customVar.name = "x";
  customVar.value = 3.5;
  customVars.push_back(customVar);
  expected = 3.5 * 3.;
  errors += testFormula("x * 3", expected, customVars, customFunctions);

  expected = 7 * 3;
  errors += testFormula("x * 3", 7, expected, customVars, customFunctions);

  expected = 3*(((5*5)));
  errors += testFormula("3*(((5*5)))", expected, customVars, customFunctions);

  expected = 3*(0)*3;
  errors += testFormula("3*()*3", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("RAND", _FormInterpreter_Random, 1., 1., 0.0));
  expected = rand() % 100;
  errors += testFormula("RAND(100)", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("AREARECTANGLE", _FormInterpreter_AreaRectangle, 1., 1., 0.0));
  expected = 3*5;
  errors += testFormula("AREARECTANGLE(3, 5)", expected, customVars, customFunctions);

  expected = 3*5*5;
  errors += testFormula("AREARECTANGLE(3, AREARECTANGLE(5,5))", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("CUBIC", _FormInterpreter_AreaCubic, 1., 1., 0.0));
  expected = 3*5*5;
  errors += testFormula("CUBIC(3, 5,5)", expected, customVars, customFunctions);

  expected = 3*5*5 * 2*2*2 * 3*3*2*1.5;
  errors += testFormula("CUBIC(AREARECTANGLE(3, AREARECTANGLE(5,5)), AREARECTANGLE(AREARECTANGLE(2,2),AREARECTANGLE(2,COS(AREARECTANGLE(1,0)))), CUBIC(3 , AREARECTANGLE(1.5, 2 ),3))", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("GEOSTAT", _FormInterpreter_GeoStat, 1., 1., 0.0));
  expected = pow(6.67259E-11 * 5.9722E24 * 86160. * 86160. / (64. * atan(1.) * atan(1.)), 1./3.);
  errors += testFormula("GEOSTAT(mEarth, 86160)", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("SUM", _FormInterpreter_Sum, 1., 1., 0.0));
  expected = 1. + 2. + 3. + 4. + 5.;
  errors += testFormula("SUM(1, 2, 3, 4, 5)", expected, customVars, customFunctions);

  expected = 1. + 2. + 3. + 4. + 5. + 5. + 6. + 7. + 8. + 9. + 10. + 11.;
  errors += testFormula("SUM(1, 2, 3, 4, 5) + SUM(5, 6, 7, 8, 9, 10, 11)", expected, customVars, customFunctions);

  expected = -1. - 2. - 3. - 4. - 5. + 5. + 6. + 7. + 8. + 9. + 10. + 11.;
  errors += testFormula("-SUM(1, 2, 3, 4, 5) + SUM(5, 6, 7, 8, 9, 10, 11)", expected, customVars, customFunctions);

  customFunctions.push_back(c_function("HALF", _FormInterpreter_Half, 1., 1., 0.0));
  expected = 10. / 2.;
  errors += testFormula("HALF(10)", expected, customVars, customFunctions);

  if (errors > 0) {
    std::cout << "---------------------" << std::endl;
    std::cout << "|     Errors: " << errors << "     |" << std::endl;
    std::cout << "---------------------" << std::endl;
  }
  else {
    std::cout << "---------------------" << std::endl;
    std::cout << "| All tests passed! |" << std::endl;
    std::cout << "---------------------" << std::endl;
  }
  return 0;
}
//-------------------------------------------
int testFormula(std::string form, double expected, std::vector<s_variable> customVars, std::vector<c_function> customFunctions)
{
  double EPS = 0.0001;
  int error = 0;
  formInterpreter xFunction(form, formInterpreter::isRad, 0.);
  std::vector<s_variable>::iterator varIter = customVars.begin();
  while (varIter != customVars.end()) {
    xFunction.defineVariable(varIter->name, varIter->value);
    varIter++;
  }
  std::vector<c_function>::iterator funcIter = customFunctions.begin();
  while (funcIter != customFunctions.end()) {
    if (funcIter->func1) xFunction.addFunction(funcIter->name, funcIter->func1, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    else if (funcIter->func2) xFunction.addFunction(funcIter->name, funcIter->func2, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    else if (funcIter->funcv) xFunction.addFunction(funcIter->name, funcIter->funcv, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    funcIter++;
  }

  double result;
  try {
    result = xFunction.calc();
  }
  catch (...) {
    std::cout << "Exception: " << xFunction.getLastError() << std::endl;
  }
  if (fabs(expected-result) > EPS) {
    std::cout << ">>>Error: Result should be " << expected << " but ";
    error = 1;
  }
  else std::cout << "OK: ";
  std::cout << form << " = " << result << std::endl;
  return error;
}
//-------------------------------------------
int testFormula(std::string form, double x, double expected, std::vector<s_variable> customVars, std::vector<c_function> customFunctions)
{
  double EPS = 0.0001;
  int error = 0;
  formInterpreter xFunction(form, formInterpreter::isRad, 0., true);
  std::vector<s_variable>::iterator varIter = customVars.begin();
  while (varIter != customVars.end()) {
    xFunction.defineVariable(varIter->name, varIter->value);
    varIter++;
  }
  std::vector<c_function>::iterator funcIter = customFunctions.begin();
  while (funcIter != customFunctions.end()) {
    if (funcIter->func1) xFunction.addFunction(funcIter->name, funcIter->func1, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    else if (funcIter->func2) xFunction.addFunction(funcIter->name, funcIter->func2, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    else if (funcIter->funcv) xFunction.addFunction(funcIter->name, funcIter->funcv, funcIter->PreFactor, funcIter->PostFactor, funcIter->PreAdd);
    funcIter++;
  }

  double result;
  try {
    result = xFunction.calc(x);
  }
  catch (...) {
    std::cout << "Exception: " << xFunction.getLastError() << std::endl;
  }
  if (fabs(expected-result) > EPS) {
    std::cout << ">>>Error: Result should be " << expected << " but ";
    error = 1;
  }
  else std::cout << "OK: ";
  std::cout << form << " = " << result << std::endl;
  return error;
}
