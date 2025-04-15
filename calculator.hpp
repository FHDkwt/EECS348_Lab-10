// header file to declare function definitions
#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

// function read_numbers for reading candidate numbers from file and returning as vector of strings
std::vector<std::string> read_numbers(const std::string& filename);

// function is_validDouble for validating whether string represents a valid double number
bool is_validDouble(const std::string& str);

// function add_strings for adding two string-formatted numbers and returning result as string
std::string add_strings(const std::string& num1, const std::string& num2);

#endif // __CALCULATOR_HPP
