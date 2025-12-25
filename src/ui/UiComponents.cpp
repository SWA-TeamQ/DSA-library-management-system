#include "ui/UiComponents.hpp"

void Row(Array<string> values, bool borderTop, int width){
    size_t totalWidth = values.size() * (width + 3) + 1;
    // border top
    cout << endl;
    if(borderTop){
        for (size_t i = 0; i < totalWidth; i++)
            cout << "-";
    }
    cout << endl;
    for (size_t i = 0; i < values.size(); i++) {
        cout << "| " << left << setw(width) << values[i] << " ";
    }
    cout << "|";
    cout << endl;
    
    // border bottom
    for (size_t i = 0; i < totalWidth; i++)
        cout << "-";
    cout << endl;
}