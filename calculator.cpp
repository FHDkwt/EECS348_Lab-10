// file containing all functions definitions
// including header file and all required libraires
#include "calculator.hpp"
#include <fstream>
#include <cctype>
#include <vector>
// defining function to parse pre-validated string as double number
double parse_number(const std::string &expression) {
    // initializing result to store parsed number
    double result = 0.0;
    // initializing flag to track if number is negative
    bool negative = false;
    // initializing position tracker for parsing string
    size_t pos = 0;
    // handling optional sign at start
    if (expression[0] == '-') 
    {
        negative = true;
        pos++;
    } else if (expression[0] == '+') 
    {
        pos++;
    }
    // parsing integer part before decimal point
    while (pos < expression.length() && std::isdigit(expression[pos]))
    {
        // building integer part digit by digit
        result = result * 10 + (expression[pos] - '0');
        pos++;
    }
    // parsing decimal part if present
    if (pos < expression.length() && expression[pos] == '.') 
    {
        pos++;
        // initializing fraction multiplier for decimal places
        double fraction = 0.1;
        while (pos < expression.length() && std::isdigit(expression[pos])) 
        {
            // adding each decimal digit to result
            result += (expression[pos] - '0') * fraction;
            fraction /= 10;
            pos++;
        }
    }
    // applying sign and return final result
    return negative ? -result : result;
}

// reading strings from a file, one per line into vector and returning empty vector if file cannot be opened
std::vector<std::string> read_numbers(const std::string& filename) {
    // vector to store read strings
    std::vector<std::string> numbers;
    // opening input file
    std::ifstream file(filename);
    // buffer for reading each line
    std::string line;
    // checking if file opened successfully
    if (!file.is_open()) 
    {
        std::cout << "Error opening file" << std::endl;
        return numbers;
    }
    // reading each line and adding non-empty lines to vector
    while (std::getline(file, line)) 
    {
        if (!line.empty()) 
        {
            numbers.push_back(line);
        }
    }
    // closing file
    file.close();
    // returning collected strings
    return numbers;
}
// validating if a string represents a valid double number   Format: (+|-)A(.B), where A is digits .B is optional but must have at least one digit 
bool is_validDouble(const std::string& str) {
    // checking for empty string
    if (str.empty())
    {
        return false;
    }
    // position tracker for parsing
    size_t pos = 0;
    // Handling optional sign
    if (str[0] == '+' || str[0] == '-')
    {
        pos++;
    }
    // ensuring string is not just sign
    if (pos == str.length())
    {
        return false;
    }
    // checking for at least one digit in integer part
    bool hasDigit = false;
    while (pos < str.length() && std::isdigit(str[pos])) 
    {
        hasDigit = true;
        pos++;
    }
    // validating decimal part if present
    if (pos < str.length()) 
    {
        // checking if there is decimal point
        if (str[pos] != '.') 
        {
            return false;
        }
        pos++;
        // checking if numbers have at least one digit after decimal
        bool hasDecimalDigit = false;
        while (pos < str.length()) 
        {
            // ensuring all remaining characters are digits
            if (!std::isdigit(str[pos]))
            {
                return false;
            }
        
            hasDecimalDigit = true;
            pos++;
        }
        // rejecting if no digits after decimal
        if (!hasDecimalDigit)
        {
            return false;
        }
    }
    // returning true only if integer part has at least one digit
    return hasDigit;
}
// defining function adding two string-formatted numbers and returning result as string
// assuming inputs are valid doubles 
std::string add_strings(const std::string& num1, const std::string& num2) {
    // declaring variables to store integer and decimal parts
    std::string int1, dec1, int2, dec2;
    // initializing neg1 flag to track signs
    bool neg1 = num1[0] == '-', neg2 = num2[0] == '-';
    // initializingdot1 to split first number into integer and decimal part
    size_t dot1 = num1.find('.');
    int1 = (neg1 ? num1.substr(1) : num1).substr(0, dot1 != std::string::npos ? dot1 : num1.length());
    dec1 = (dot1 != std::string::npos) ? num1.substr(dot1 + 1) : "";
    // initializing dot2 to split second number into integer and decimal part
    size_t dot2 = num2.find('.');
    int2 = (neg2 ? num2.substr(1) : num2).substr(0, dot2 != std::string::npos ? dot2 : num2.length());
    dec2 = (dot2 != std::string::npos) ? num2.substr(dot2 + 1) : "";
    // initializing maxDec to align decimal parts by padding with zeros
    size_t maxDec = std::max(dec1.length(), dec2.length());
    dec1 += std::string(maxDec - dec1.length(), '0');
    dec2 += std::string(maxDec - dec2.length(), '0');
    // declaring result string and initializing carry for addition
    std::string result;
    int carry = 0;
    // adding decimal parts from right to left
    for (int i = maxDec - 1; i >= 0; i--) 
    {
        int sum = (dec1[i] - '0') + (dec2[i] - '0') + carry;
        carry = sum / 10;
        result = std::to_string(sum % 10) + result;
    }
    // adding decimal point if decimal parts
    if (maxDec > 0)
    {
        result = "." + result;
    }
    // initializing maxInt,int1,int2 to align integer parts by padding with zeros
    int maxInt = std::max(int1.length(), int2.length());
    int1 = std::string(maxInt - int1.length(), '0') + int1;
    int2 = std::string(maxInt - int2.length(), '0') + int2;
    // adding integer parts from right to left
    for (int i = maxInt - 1; i >= 0; i--) 
    {
        int sum = (int1[i] - '0') + (int2[i] - '0') + carry;
        carry = sum / 10;
        result = std::to_string(sum % 10) + result;
    }
    // if present append carry 
    if (carry)
    {
        result = "1" + result;
    }
    // normalizing result by removing trailing zeros in decimal part
    if (result.find('.') != std::string::npos) 
    {
        while (result.back() == '0')
        {
            result.pop_back();
        }
        if (result.back() == '.')
        {
            result.pop_back();
        }
    }
    // normalizing result by removing leading zeros in integer part
    size_t start = (result[0] == '-' ? 1 : 0);
    while (start < result.length() && result[start] == '0' && start + 1 < result.length() && result[start + 1] != '.') 
    {
        result.erase(start, 1);
    }
    // handling edge cases for zero
    if (start > 0 && result.length() == 1)
    {
        result = "0";
    }
    if (result == "-0")
    {
        result = "0";
    }
    // handling signs for result
    if (neg1 && neg2) 
    {
        // result is negative if both negative
        return "-" + result;
    } 
    else if (neg1 && !neg2) 
    {
        return result;
    } 
    else if (!neg1 && neg2) 
    {
        return result;
    }
    // returning result
    return result;
}
