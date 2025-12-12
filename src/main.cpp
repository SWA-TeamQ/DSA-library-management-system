#include "core/LibraryController.hpp"
#include "ui/ConsoleInterface.hpp"
using namespace std;

int main() {
    LibraryController controller;
    ConsoleInterface ui(controller);
    ui.run();
    return 0;
}
