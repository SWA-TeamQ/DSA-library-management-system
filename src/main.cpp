#include "core/LibraryController.hpp"
#include "ui/ConsoleInterface.hpp"
using namespace std;

int main() {
    LibraryController controller;
    controller.load(); // Load existing data
    
    ConsoleInterface ui(controller);
    ui.run();
    
    controller.save(); // Save data before exiting
    return 0;
}
