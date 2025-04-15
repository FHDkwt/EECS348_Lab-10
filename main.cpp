// including header file and required libraries
#include <iostream>
#include <string>
#include "calculator.hpp"

// main function to process numbers from file and perform addition
int main(int argc, char *argv[]) {
    // declaring filename variable to store input file name 
    std::string filename;
    // checking if file name provided as a command-line argument
    if (argc > 1) 
    {
        filename = argv[1];
    } 
    else 
    {
        // prompting user for file name if not provided
        std::cout << "Enter input file name: ";
        std::cin >> filename;
    }
    // reading numbers from file using read_numbers function
    std::vector<std::string> numbers = read_numbers(filename);
    // defining constant number to add to each valid number
    const std::string constant = "-123.456";
    // processing each number in file
    for (const auto& num : numbers)
      {
        // printing number being processed
        std::cout << "Processing number: " << num << std::endl;
        // validating if number is a valid double
        if (!is_validDouble(num)) 
        {
            // printing error for invalid numbers
            std::cout << num << " is not a valid double number" << std::endl;
            continue;
        }
        // adding valid number to constant
        std::string result = add_strings(num, constant);
        // printing addition result
        std::cout << num << " + " << constant << " = " << result << std::endl;
    }
    // retuning 0 to indicate successful completion
    return 0;
}
