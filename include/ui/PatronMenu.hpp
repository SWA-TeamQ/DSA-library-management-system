#pragma once
#include <iostream>
#include <string>
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"
#include "ui/UiComponents.hpp"
#include "ui/Schemas.hpp"

using namespace std;
class PatronMenu
{
public:
    PatronMenu(LibraryController &controller) : controller(controller) {}
    void show();
    
private:
    LibraryController &controller;

    void listPatrons();
    void removePatron();
    void addPatron();
    void updatePatron();
    void searchPatrons();
    void sortPatrons();

};

