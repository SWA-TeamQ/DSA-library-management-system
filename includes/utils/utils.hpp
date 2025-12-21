#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>



namespace Utils {

    // Step 2.1: Date Helper
    std::string getCurrentDate();
    
    // Step 2.2: Date Helper
    int daysBetween(const std::string& d1, const std::string& d2);

    // Step 3.1: Numeric Input Guard
    bool isValidNumber(const std::string& input);

    // Step 4.1: ISBN Validation
    bool isValidISBN(const std::string& isbn);

    // Step 5.1: Name Validation
    bool isValidName(const std::string& name);

}

#endif // UTILS_HPP
