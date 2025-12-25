#pragma once
#include <string>
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"

using namespace std;
class PatronMenu
{
public:
    PatronMenu(LibraryController &controller) : controller(controller) {}
    void show();
    
private:
    LibraryController &controller;

    void listPatrons();
    void addPatron();
    void removePatron();
    void updatePatron();
    void searchPatrons();
    void sortPatrons();

};

