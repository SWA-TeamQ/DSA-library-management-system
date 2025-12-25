#include "ui/UiComponents.hpp"

void Row(Array<string> values, bool borderTop = false, int width = 15){
    size_t totalWidth = values.size() * (width + 3) + 1;
    // border top
    if(borderTop){
        for (size_t i = 0; i < totalWidth; i++)
            cout << "-";
    }

    for (size_t i = 0; i < values.size(); i++) {
        cout << "| " << left << setw(width) << values[i] << " ";
    }
    cout << "|\n";

    // border bottom
    for (size_t i = 0; i < totalWidth; i++)
        cout << "-";
    cout << "\n";
}