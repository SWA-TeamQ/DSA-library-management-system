#include <iostream>
#include <string>
#include "../../includes/core/LoanService.hpp"
#include "../../includes/core/Transaction.hpp" 
#include "../../includes/utils/utils.hpp"

namespace {

// File-local counters for ID generation
int transactionCounter = 1000;
int patronCounter = 2000;

// ID generators (private to this file)
std::string generateTransactionID() {
    return "TXN-" + std::to_string(++transactionCounter);
}

std::string generatePatronID() {
    return "USR-" + std::to_string(++patronCounter);
}

} // end anonymous namespace

namespace LoanService {

void borrowBook(const std::string& patronId, const std::string& isbn) {
    std::string txnId = generateTransactionID();
    std::string currentDate = Utils::getCurrentDate();

    std::cout << "[LoanService] Generated Transaction ID: "
              << txnId << " for Patron: " << patronId << std::endl;
}

void registerPatron(const std::string& name) {
    if (!Utils::isValidName(name)) {
        std::cout << "Error: Invalid patron name '" << name << "'" << std::endl;
        return;
    }

    std::string newPatronId = generatePatronID();
    std::cout << "Patron Registered: "
              << newPatronId << " - " << name << std::endl;
}

}

