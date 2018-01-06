/*
Expression is a C++ class to evaluate a mathematical formula containing multiple variables and functions.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef FORMINTERPRETER_H
#define FORMINTERPRETER_H

#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

//---------------------------------------------------------------------------
class FormulaException
{
public:
  unsigned int Id;
  std::string Message;
  FormulaException(unsigned int Nummer, std::string Text, bool printText = false)
  {
    Id = Nummer;
    Message = Text;
    if (printText) std::cout << Id << ": " << Message << std::endl;
  }
};
class c_func_base {};
//-------------------------------------------------------------------------------------
//template <typename... Args>
class c_function : c_func_base {
public:
  c_function(std::string fname, double (*ffunction)(double), double preFactor = 1., double postFactor = 1., double preAdd = 0.) {
    name = fname;
    argumentCount = 1;
    func1 = ffunction;
    func2 = NULL;
    funcv = NULL;
    PreFactor  = preFactor;  // factor to be used before processing the function
    PostFactor = postFactor; // factor to be used after processing the function
    PreAdd = preAdd;         // value to be added before processing the function
    isDirect = true;
  };
  c_function(std::string fname, double (*ffunction)(double, double), double preFactor = 1., double postFactor = 1., double preAdd = 0.) {
    name = fname;
    argumentCount = 2;
    func1 = NULL;
    func2 = ffunction;
    funcv = NULL;
    PreFactor  = preFactor;  // factor to be used before processing the function
    PostFactor = postFactor; // factor to be used after processing the function
    PreAdd = preAdd;         // value to be added before processing the function
    isDirect = true;
  };
  c_function(std::string fname, double (*ffunction)(std::vector<double>), double preFactor = 1., double postFactor = 1., double preAdd = 0.) {
    name = fname;
    argumentCount = 3;
    func1 = NULL;
    func2 = NULL;
    funcv = ffunction;
    PreFactor  = preFactor;  // factor to be used before processing the function
    PostFactor = postFactor; // factor to be used after processing the function
    PreAdd = preAdd;         // value to be added before processing the function
    isDirect = false;
  };
  ~c_function(){};
  std::string name;
  unsigned int argumentCount;
//  double (*function)(Args...);
  double (*func1)(double);
  double (*func2)(double, double);
  double (*funcv)(std::vector<double>);
  double PreFactor;
  double PostFactor;
  double PreAdd;
  bool isDirect;
};
//-------------------------------------------------------------------------------------
class c_operator {
public:
  c_operator() {
    osymbol = ' ';
    olevel = 0;
  };
  c_operator(char symbol, int level) {
    osymbol = symbol;
    olevel = level;
  };
  char osymbol;
  int olevel;
};
//-------------------------------------------------------------------------------------
class formInterpreter
{
private:
  void initOperators();                              // initialize operator symbols + - * etc.
  void initVariables();                              // initialize constant values
  bool checkBalanceOfParenteses(std::string form);   // check the balance of parenteses in formula
  std::string replaceVariables();                    // replaces all variable names with their values
  void setVariable(std::string name, bool valid);    // sets a variable to valid or invalid.
  double processFormula(double val1, c_operator op1, std::string form, int *newpos);
  c_operator getNextOperator(char opstr);                  // get the next operator and check if it is valid
  bool getNextValue(std::string line, double *number, int *newPos);   // reads a value from the formula
  unsigned int getClosingParenthesis(std::string form, int start);    // searchs the matching closing parenthesis for an opening one
  std::map<char, c_operator> operators;              // map of operators
  struct s_variable {     // structure to hold variable definitions
    std::string name;     // name of a variable
    double value;         // value of a variable
    bool valid;           // flag to switch a variable on and off (internal use)
    bool operator<(const s_variable& a) const // operator to sort variable definition by length of variable name
    {
        return name.size() > a.name.size();   // note that ">" is used because we need the longest names first
    }
  };
  std::vector<s_variable> variables;          // here the defined variables are stored
  template <typename T>
  std::string toString(T number)                  //converts number to string
  {
    std::ostringstream strs;
    strs << std::setprecision(8) << std::fixed << number;
    std::string str = strs.str();
    return str;
  }
  std::vector<std::string> split(const std::string s, char delim);
  void throwException(int number, std::string text);
  bool printExceptionText;
  std::string lastError;
  std::vector<s_variable>::iterator checkVariable(std::string name); // check a variable for existence in the variable list
  void cleanFunctionVector();
public:
  enum angleType {
    isRad    = 1,
    isDegree = 2,
    isGon    = 3
  };
  formInterpreter();
  formInterpreter(std::string formula, angleType type = isRad, double round = 0., bool doExceptionText = false);
  void set(std::string formula, angleType type = isRad, double round = 0., bool doExceptionText = false);
  ~formInterpreter();
  void initFormula(std::string formula);             // initialization of the formula
  void initFunctions(angleType type, double round);  // initialization of math functions
  double calc();                                     // replaces all defined variables and calculates result
  double calc(double x);                             // replaces x with the passed parameter and calculates result
  void defineVariable(std::string name, double value);  // adds a variable by name and value
  void deleteVariable(std::string name);             // delete a variable by its name
  bool checkVariableExists(std::string name); // check a variable for existence in the variable list
  double getVariable(std::string name);              // get the value of a variable;
  void clearVariables();                             // clears all variables
// add custom function with one argument
  void addFunction(std::string fname,
                   double (*ffunction)(double),
                   double preFactor = 1.,
                   double postFactor = 1.,
                   double preAdd = 0.);
// add custom function with two arguments
  void addFunction(std::string fname,
                   double (*ffunction)(double, double),
                   double preFactor = 1.,
                   double postFactor = 1.,
                   double preAdd = 0.);
// add custom function with three arguments
  void addFunction(std::string fname,
                   double (*ffunction)(std::vector<double>),
                   double preFactor = 1.,
                   double postFactor = 1.,
                   double preAdd = 0.);
  bool supports(std::string functionName);           // query if a function is supported
  bool conflicts(std::string variableName);          // query if a variable name conflicts with a function name
  std::string getLastError();
protected:
  std::vector<c_function*> functions;                // functions that are supported. defined in constructor.
  std::string replaceAll(const std::string& str, const std::string& from, const std::string& to); // Replaces strings
  std::string formula;                               // this string holds the formula that will be interpreted
  double interpret(std::string form);                // interprets the formula and calcs the result (called by calc() and calc(double)
};
#endif // EXPRESSION_H
