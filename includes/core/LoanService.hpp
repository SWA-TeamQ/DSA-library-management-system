#ifndef LOAN_SERVICE_HPP
#define LOAN_SERVICE_HPP

#include <string>

namespace LoanService {

    // Handles borrowing request (ID generation & logging handled internally)
    void borrowBook(const std::string& patronId, const std::string& isbn);
    
    // Registers a new patron
    void registerPatron(const std::string& name);

}

#endif // LOAN_SERVICE_HPP