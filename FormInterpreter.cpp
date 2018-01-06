/*
formInterpreter is a C++ class to evaluate a mathematical formula containing multiple variables and functions.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#include <algorithm>
#include "FormInterpreter.h"
//-------------------------------------------------------------------------------------
// Mathematical formula interpreter.
// Processes formulas like 2*3+x^4.
// Easy to use function calc(double) if just one variable is used
// Any number of variables can be used if needed.
// Supported mathematical functions: see constructor.
//-------------------------------------------------------------------------------------
formInterpreter::formInterpreter()
{
}
//-------------------------------------------------------------------------------------
formInterpreter::formInterpreter(std::string formula, angleType type, double round, bool doExceptionText)
{
  set(formula, type, round, doExceptionText);
}
//-------------------------------------------------------------------------------------
formInterpreter::~formInterpreter()
{
  cleanFunctionVector();
}
//-------------------------------------------------------------------------------------
void formInterpreter::cleanFunctionVector()
{
  std::vector<c_function*>::iterator funcIter = functions.begin();
  while (funcIter != functions.end()) {
//    std::cout << (*funcIter)->name << std::endl;
    delete *funcIter;
    funcIter++;
  }
}
//-------------------------------------------------------------------------------------
void formInterpreter::set(std::string formula, angleType type, double round, bool doExceptionText)
{
  printExceptionText = doExceptionText;
  // Check if parenthesis are balanced
  initFormula(formula);
  // init function vector
  initFunctions(type, round);
  // init the operators
  initOperators();
  // init Constants like e, pi etc.
  initVariables();
}
//-------------------------------------------------------------------------------------
// check and prepare formula
//
void formInterpreter::initFormula(std::string formula)
{
    // Check if parentheses are balanced
  if (!checkBalanceOfParenteses(formula)) throwException(10, "Expression: Unbalanced () in " + formula);
  // remove all white spaces from the formular
  formula = replaceAll(formula, " ", "");
  formula = replaceAll(formula, "\t", "");
  // store formula
  this->formula = formula;
}
//-------------------------------------------------------------------------------------
// initialize the supported math functions
//
void formInterpreter::initFunctions(angleType type, double round)
{
  // define factors to calculate with Rad, Degree or Gon
  double trigFactor = 1.;
  if (type == isRad) trigFactor         = 1.;
  else if (type == isDegree) trigFactor = 180. / M_PI;
  else if (type == isGon) trigFactor    = 200. / M_PI;
  // randomize
  srand (time(NULL));
  // vector containing supported functions containing:
  // 1: function name as expected in the formula. Uppercase to avoid confusion with variables
  // 2: function itself
  // 3: factor to be multiplied with argument before calculation
  // 4: factor to be multiplied with result of calculation
  // 5: value to be added before operation (for rounding)
  cleanFunctionVector();
  functions.clear();
  functions.push_back(new c_function("SIN"  , sin  , 1./trigFactor, 1., 0.0));       // sinus argument
  functions.push_back(new c_function("COS"  , cos  , 1./trigFactor, 1., 0.0));       // cosinus argument
  functions.push_back(new c_function("TAN"  , tan  , 1./trigFactor, 1., 0.0));       // tangens argument
  functions.push_back(new c_function("ASIN" , asin , 1.           , trigFactor, 0.0)); // arcussinus result
  functions.push_back(new c_function("ACOS" , acos , 1.           , trigFactor, 0.0)); // arcuscosinus result
  functions.push_back(new c_function("ATAN" , atan , 1.           , trigFactor, 0.0)); // arcustangens result
  functions.push_back(new c_function("ATAN2", atan2, 1.           , trigFactor, 0.0)); // arcustangens result
  functions.push_back(new c_function("SQRT" , sqrt , 1.           , 1., 0.0));       // squareroot
  functions.push_back(new c_function("ABS"  , fabs , 1.           , 1., 0.0));       // absolut value
  functions.push_back(new c_function("FLOOR", floor, 1.           , 1., round));     // next smaller integer
  functions.push_back(new c_function("EXP"  , exp  , 1.           , 1., 0.0));       // exponent base e
  functions.push_back(new c_function("LOG"  , log  , 1.           , 1., 0.0));       // logarithm base e
  functions.push_back(new c_function("LOG10", log10, 1.           , 1., 0.0));       // logarithm base 10
}
//-------------------------------------------------------------------------------------
// add a function with one argument
//
void formInterpreter::addFunction(std::string fname,
                                  double (*ffunction)(double),
                                  double preFactor, double postFactor, double preAdd)
{
  if (supports(fname)) throwException(30, "Formula: Function " + fname + " already exists!");
  else functions.push_back(new c_function(fname , ffunction, preFactor, postFactor, preAdd));
}
//-------------------------------------------------------------------------------------
// add a function with two arguments
//
void formInterpreter::addFunction(std::string fname,
                                  double (*ffunction)(double, double),
                                  double preFactor, double postFactor, double preAdd)
{
  if (supports(fname)) throwException(30, "Formula: Function " + fname + " already exists!");
  else functions.push_back(new c_function(fname , ffunction, preFactor, postFactor, preAdd));
}
//-------------------------------------------------------------------------------------
// add a function with multiple arguments
//
void formInterpreter::addFunction(std::string fname,
                                  double (*ffunction)(std::vector<double>),
                                  double preFactor, double postFactor, double preAdd)
{
  if (supports(fname)) throwException(30, "Formula: Function " + fname + " already exists!");
  else functions.push_back(new c_function(fname , ffunction, preFactor, postFactor, preAdd));
}
//-------------------------------------------------------------------------------------
// initialize opeartors
//
void formInterpreter::initOperators()
{
  // the operators contain the operator symbol (+, -, *...) and a value representing
  // the priority for calculation to ensure that ^ is processed before * and / which is processed before + and -.
  operators.insert(std::pair<char, c_operator>('+', c_operator('+', 0)));
  operators.insert(std::pair<char, c_operator>('-', c_operator('-', 0)));
  operators.insert(std::pair<char, c_operator>('*', c_operator('*', 1)));
  operators.insert(std::pair<char, c_operator>('/', c_operator('/', 1)));
  operators.insert(std::pair<char, c_operator>('^', c_operator('^', 2)));
}
//-------------------------------------------------------------------------------------
// Check if parentheses are balanced and if a closing parenthesis does not have
// a preceding opening parenthesis.
//
bool formInterpreter::checkBalanceOfParenteses(std::string form)
{
  int par = 0;
  std::string::iterator sIter = form.begin();
  while (sIter != form.end()) {
    if (*sIter == '(') par++;
    else if (*sIter == ')') par--;
    if (par < 0) return false;
    sIter++;
  }
  if (par != 0) return false;

  return true;
}
//-------------------------------------------------------------------------------------
// Query if the given function (like SIN etc.) is supported
//
bool formInterpreter::supports(std::string functionName)
{
  bool rc = false;
  std::vector<c_function*>::iterator funcIter = functions.begin();
  while (funcIter != functions.end()) {
    if (functionName.find((*funcIter)->name) == 0) {
        // function name is supported
        rc = true;
        break;
      }
      funcIter++;
    }
  return rc;
}
//-------------------------------------------------------------------------------------
// Query if the given variable name matchs the whole or a part of a function name
//
bool formInterpreter::conflicts(std::string variableName)
{
  bool rc = false;
  std::vector<c_function*>::iterator funcIter = functions.begin();
  while (funcIter != functions.end()) {
    if ((*funcIter)->name.find(variableName) != std::string::npos) {
        // variable is part of a function name
        rc = true;
        break;
      }
      funcIter++;
    }
  return rc;
}
//-------------------------------------------------------------------------------------
// Calculate an formula containing x as variable (for convenience) so the
// variable x must not be defined by addVariable().
// Attention: If a variable x is defined by addVariable(), the passed
// x-value is used instead of the x-value in the variable list!
//
double formInterpreter::calc(double x)
{
  double result = 0.0;
  // set a possibly defined x variable to invalid to avoid replacement with
  // this value instead of the passed one.
  setVariable("x", false);
  // replace all defined variables with their values
  std::string formulaVarsReplaced = replaceVariables();
  // set a possibly defined x variable to valid again
  setVariable("x", true);
  // replace the character x with string containing value of x
  std::string numberString = toString<double>(x);
  formulaVarsReplaced = replaceAll(formulaVarsReplaced, "x", numberString);
  // interpret the formula
  result = interpret(formulaVarsReplaced);
  return result;
}
//-------------------------------------------------------------------------------------
// Calculate an formula containing the defined variables (see addVariable)
//
double formInterpreter::calc()
{
  double result = 0.0;
  // interpret the formula
  result = interpret(replaceVariables());
  return result;
}
//-------------------------------------------------------------------------------------
// initialize variables
//
void formInterpreter::initVariables()
{
  defineVariable("Pi", 4 * atan(1.));  // Value of Pi
  defineVariable("Euler", 2.71828182845904523536); // Euler Number
  defineVariable("g", 6.67259E-11); // N * m^2 / kg^2 - Constant of gravitation
  defineVariable("mEarth", 5.9722E24); // kg - Mass of Earth
}
//-------------------------------------------------------------------------------------
// replace all variablenames by their values and return the resulting function string
//
std::string formInterpreter::replaceVariables()
{
  // init the result with the original formula
  std::string result = formula;
  // sort the vector by length of variable names, longest first (see operator < in struct s_variable)
  // to avoid replacing an equal part of a longer variable name with the wrong shorter variable name.
  std::sort(variables.begin(), variables.end());
  // fill in the variables
  std::vector<s_variable>::iterator vIter = variables.begin();
  while (vIter != variables.end()) {
    if (vIter->valid)
     {
      std::string numberString = toString<double>(vIter->value);
      result = replaceAll(result, vIter->name, numberString);
    }
    vIter++;
  }
  return result;
}
//-------------------------------------------------------------------------------------
// Add a variablename/variablevalue pair
//
void formInterpreter::defineVariable(std::string name, double value)
{
//  if (supports(name)) throwException(30, "Formula: defineVariable: " + name + " already exists as function name!");
  if (conflicts(name)) throwException(31, "Formula: defineVariable: " + name + " conflicts with function name!");
  // check if the variable already exists and replace its value
  // if the variable is marked as invalid, switch this flag to true
  std::vector<s_variable>::iterator varIter = checkVariable(name);
  if (varIter != variables.end()) {
    varIter->value = value;
    varIter->valid = true;
  }
  // if variable did not exist add it to the vector
  else {
    s_variable variable;
    variable.name = name;
    variable.value = value;
    variable.valid = true;
    variables.push_back(variable);
  }
}
//-------------------------------------------------------------------------------------
// Check if a variable exists in the variable list and return its iterator. This method
// is used oly within the class (private)
//
std::vector<formInterpreter::s_variable>::iterator formInterpreter::checkVariable(std::string name)
{
  std::vector<s_variable>::iterator result = variables.end();
  // check if the variable exists
  std::vector<s_variable>::iterator varIter = variables.begin();
  while (varIter != variables.end()) {
    if (varIter->name == name) {
      result = varIter;
      break;
    }
    varIter++;
  }
  return result;
}
//-------------------------------------------------------------------------------------
// Check if a variable exists in the variable list and return true or false
//
bool formInterpreter::checkVariableExists(std::string name)
{
  bool result = false;
  if (formInterpreter::checkVariable(name) != variables.end()) result = true;
  return result;
}
//-------------------------------------------------------------------------------------
// Get the value of a variable
//
double formInterpreter::getVariable(std::string name)
{
  double result = 0.0;
  std::vector<s_variable>::iterator varIter;
  if ((varIter = checkVariable(name)) != variables.end()) {
    result = varIter->value;
  }
  else {
    // if variable did not exist throw an exeption.
    // to avoid that use the method checkVariable() first.
    throwException(20, "Formula: Variable " + name + " does not exist in variable list!");
  }
  return result;
}
//-------------------------------------------------------------------------------------
// Remove a variable from the variable list
//
void formInterpreter::deleteVariable(std::string name)
{
  std::vector<s_variable>::iterator varIter;
  if ((varIter = checkVariable(name)) != variables.end()) {
    variables.erase(varIter);
  }
}
//-------------------------------------------------------------------------------------
// set a variable to valid or invalid by passing true or false.
// if the variable does not exist, the method has no effect and does not
// throw an exception.
// This is an internal method that avoids mixup with a predefined variable "x"
// when using the method calc(x).
//
void formInterpreter::setVariable(std::string name, bool valid)
{
  // check if the variable exists
  std::vector<s_variable>::iterator varIter = variables.begin();
  while (varIter != variables.end()) {
    if (varIter->name == name) {
      varIter->valid = valid;
      break;
    }
    varIter++;
  }
}
//-------------------------------------------------------------------------------------
void formInterpreter::clearVariables()
{
  variables.clear();
  initVariables();
}
//-------------------------------------------------------------------------------------
// interpret the formula in string form
//
double formInterpreter::interpret(std::string form)
{
  double rc = 0.0;
  int newpos;
  // get the first value (a value may be a number, a function or something enclosed in parentheses
  if (!getNextValue(form, &rc, &newpos)) throwException(11, "Formula: Error in " + form);
  size_t n = newpos;
  // now loop through the remaining formula
  while (n < form.size()) {
    // get the next operator (+, -, * ....)
    c_operator op1;
    op1 = getNextOperator(form.at(n++));
    // process the remaining formula
    rc = processFormula(rc, op1, form.substr(n), &newpos);
    n += newpos;
  }
  return rc;
}
//-------------------------------------------------------------------------------------
// process a part of a formula as long the operator does not have lower priotity as the passed one
//
double formInterpreter::processFormula(double val1, c_operator op1, std::string form, int *newpos)
{
  double val2;
  size_t n = 0;
  int olevel = op1.olevel;
  // we will repeat that until the priotity of the operator differs from the passed one
  while (op1.olevel == olevel) {
    c_operator op2;
    // get the next value behind the operator
    if (!getNextValue(form.substr(n), &val2, newpos)) throwException(13, "Formula: Error in " + form);
    n += *newpos;
    // check if next operator has higher priority: This has to be processed first
    if (n < form.size()) {
      op2 = getNextOperator(form.at(n));
      // check the priority
      while (op2.olevel > op1.olevel) {
        n++;
        // the priority is higher, so process the next part of the formula first
        // until an operator with lower priority is found.
        val2 = processFormula(val2, op2, form.substr(n), newpos);
        n += *newpos;
        // check if we must continue with sub-processing (for example the * in 2 + 2^2 * 2)
        if (n < form.size()) op2 = getNextOperator(form.at(n));
        else break;
      }
    }
    // process the operator
    if (op1.osymbol == '+') val1 += val2;
    else if (op1.osymbol == '-') val1 -= val2;
    else if (op1.osymbol == '*') val1 *= val2;
    else if (op1.osymbol == '/') val1 /= val2;
    else if (op1.osymbol == '^') val1 = pow(val1, val2);
    // read next operator
    if (n < form.size()) {
      op1 = getNextOperator(form.at(n));
      if (op1.olevel == olevel) n++;
    }
    else break;
  }
  *newpos = n;
  return val1;
}
//-------------------------------------------------------------------------------------
// get the next operator
//
c_operator formInterpreter::getNextOperator(char opstr)
{
  c_operator op;
  std::map<char, c_operator>::iterator operIter = operators.find(opstr);
  if (operIter == operators.end()) throwException(15, "Formula: Operator " + std::string(1,opstr) + " not supported!");
  op = operIter->second;
  return op;
}
//-------------------------------------------------------------------------------------
// get the next value in the formula.
// if the formula starts with opening parenthesis we return the whole
// sub-formula within the parenthesis. Functions will also processed.
//
bool formInterpreter::getNextValue(std::string form, double *number, int *newPos)
{
  if (form.size() < 1) return false;
  // We check for preceeding + or -
  if (form.at(0) == '+') {
    if (!getNextValue(form.substr(1), number, newPos)) throwException(11, "Formula: Error in " + form);
    (*newPos)++;
  }
  else if (form.at(0) == '-') {
    if (!getNextValue(form.substr(1), number, newPos)) throwException(11, "Formula: Error in " + form);
    *number = -(*number);
    (*newPos)++;
  }
  // When an opening parenthesis is found, we first evaluate the whole part in this parenthesis
  else if (form.at(0) == '(') {
    *newPos = getClosingParenthesis(form, 0);
    if (*newPos <= 1) return false;
    // the part in parenthesis is recursively interpreted like a separate formula
    *number = interpret(form.substr(1, *newPos - 1));
    *newPos = *newPos + 1;
  }
  else {
    // check if any of the functions in the functionvector matches the next part of the formula
    std::vector<c_function*>::iterator funcIter = functions.begin();
    while (funcIter != functions.end()) {
      if (form.find((*funcIter)->name) == 0) {
        // we have a function name. check if the following term is placed in parenthesis.
        // If not, we might have another function that starts with the same characters
        // (for example ATAN is found but ATAN2 is next in the formula)
        int funcLen = (*funcIter)->name.size();
        if (form.at(funcLen) != '(') {
          // proceed testing for the next function
          funcIter++;
          continue;
        }
        *newPos = getClosingParenthesis(form, funcLen);
        if (*newPos == funcLen) return false;
        // now the part within the parentheses is interpreted.
        // depending on the number of arguments we have to split the contents between the parentheses
        // by comma. Because other functions with comma can exist within an Argument, we take a temp
        // stringvector first and then check the balances to build a vector with the valid arguments.
        std::vector<std::string> tempArguments = split(form.substr(funcLen+1, *newPos - (funcLen+1)), ',');
        *newPos = *newPos + 1;
        std::vector<std::string> arguments;
        // check for balances
        std::string argument;
        std::vector<std::string>::iterator targIter = tempArguments.begin();
        while (targIter != tempArguments.end()) {
          argument += *targIter;
          // if the parenteses in the argument are balanced we assume that the argument is complete
          if (checkBalanceOfParenteses(argument)) {
            arguments.push_back(argument);
            argument.clear();
          }
          else {
            // a comma must be re-inserted because this is a sub-formula separated at comma at a later time
            argument += ",";
          }
          targIter++;
        }
        // we check if the number of arguments fits the function
        if ((*funcIter)->isDirect == true) {
          if ((*funcIter)->argumentCount != arguments.size()) {
            throwException(21, "Formula: Number of Arguments in function >" + (*funcIter)->name + "< seems to be wrong");
          }
        }
        // now we process the arguments of the function.
        std::vector<double> dblArgs;
        std::vector<std::string>::iterator argIter = arguments.begin();
        while (argIter != arguments.end()) {
          dblArgs.push_back(interpret(*argIter));
          argIter++;
        }
        // the interpreted part between the parenthesis is passed to the function.
        // factors are needed for trigonometric functions to convert degree to radian and vice versa.
        // the values of the factors/preadd are defined in the function entry of the vector (see constructor).
        // depending on the number of arguments we use different function calls:
        if ((*funcIter)->argumentCount == 1) {
          if ((*funcIter)->isDirect) {
            *number = (*funcIter)->func1(dblArgs.at(0) * (*funcIter)->PreFactor + (*funcIter)->PreAdd)
                                         * (*funcIter)->PostFactor;
          }
          else {
            *number = (*funcIter)->funcv(dblArgs) * (*funcIter)->PostFactor;
          }
        }
        else if ((*funcIter)->argumentCount == 2) {
          if ((*funcIter)->isDirect) {
            *number = (*funcIter)->func2(dblArgs.at(0) * (*funcIter)->PreFactor + (*funcIter)->PreAdd,
                                         dblArgs.at(1) * (*funcIter)->PreFactor + (*funcIter)->PreAdd) *
                                         (*funcIter)->PostFactor;
          }
          else {
            *number = (*funcIter)->funcv(dblArgs) * (*funcIter)->PostFactor;
          }
        }
        else if ((*funcIter)->argumentCount > 2) {
          *number = (*funcIter)->funcv(dblArgs) * (*funcIter)->PostFactor;
        }
        break;
      }
      funcIter++;
    }
    // No function is found, so read a number
    if (funcIter == functions.end()) {
      // read a number
      std::istringstream inString(form);
      inString >> *number;
      if ( (inString.rdstate() & std::ifstream::failbit ) != 0 ) {
        throwException(16, "Formula: Value expected in >" + form + "<! Are function names in upper case?");
      }
      if ( (inString.rdstate() & std::ifstream::eofbit ) != 0 ) {
        // on some compilers this is done by inString.tellg() but with CentOs tellg() returns -1 on Eof
        *newPos = form.size();
      }
      else {
        *newPos  = inString.tellg();
      }
    }
  }
  return true;
}
//-------------------------------------------------------------------------------------
// search the closing parenthesis that matches the opening parentesis at position pos.
// returns 0 if there is no closing parentesis.
//
unsigned int formInterpreter::getClosingParenthesis(std::string form, int pos)
{
  int parenthesis = 0;
//  int rc = start;
  for (unsigned int i=pos; i<form.size(); i++) {
    if (form.at(i) == '(') parenthesis++;
    else if (form.at(i) == ')') parenthesis--;
    if (parenthesis == 0) {
      // set pos to the position of the matching closing parentesis.
      // if there is no matching closing parentesis pos remains 0.
      pos = i;
      break;
    }
  }
  return pos;
}
//-------------------------------------------------------------------------------------
void formInterpreter::throwException(int number, std::string text)
{
  lastError = text;
  throw FormulaException(number, text, printExceptionText);
}
//-------------------------------------------------------------------------------------
std::string formInterpreter::getLastError()
{
  return lastError;
}
//-------------------------------------------------------------------------------------
std::string formInterpreter::replaceAll(const std::string& str, const std::string& from, const std::string& to)
{
  if (from.empty()) return str;
  std::string result = str;
  size_t start_pos = 0;
  while((start_pos = result.find(from, start_pos)) != std::string::npos) {
    result.replace(start_pos, from.length(), to);
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
  return result;
}
//-------------------------------------------------------------------------------------
std::vector<std::string> formInterpreter::split(const std::string s, char delim)
{
  std::vector<std::string> elements;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (!item.empty()) elements.push_back(item);
  }
  return elements;
}
