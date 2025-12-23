#pragma once

#include <string>
#include "core/LibraryController.hpp"

class PatronMenu
{
public:
    explicit PatronMenu(LibraryController &controller) : controller(controller) {}
    void show();

private:
    LibraryController &controller;

    std::string readLine(const std::string &prompt) const;
    int readInt(const std::string &prompt) const;
    void waitForEnter() const;
};

