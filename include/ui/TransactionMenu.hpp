#pragma once

#include <string>
#include "core/LibraryController.hpp"

class TransactionMenu
{
public:
    explicit TransactionMenu(LibraryController &controller) : controller(controller) {}
    void show();

private:
    LibraryController &controller;

    std::string readLine(const std::string &prompt) const;
    void waitForEnter() const;
};
