// header file to declare function definitions
#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

// reading candidate numbers from file and returning as vector of strings
std::vector<std::string> readNumbers(const std::string& filename);

// validating whether string represents a valid double number
bool isValidDouble(const std::string& str);

// adding two string-formatted numbers and returning result as string
std::string addStrings(const std::string& num1, const std::string& num2);

#endif // __CALCULATOR_HPP
