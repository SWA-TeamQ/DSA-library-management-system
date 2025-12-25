#include <iostream>
#include <iomanip>
#include <string>
#include "dsa/Array.hpp"

using namespace std;

void Row(Array<string>& values, bool borderTop = false, int width = 15) {
    int totalWidth = values.size() * (width + 3) + 1;
    // border top
    if(borderTop){
        for (int i = 0; i < totalWidth; i++)
            cout << "-";
    }

    for (int i = 0; i < values.size(); i++) {
        cout << "| " << left << setw(width) << values[i] << " ";
    }
    cout << "|\n";

    // border bottom
    for (int i = 0; i < totalWidth; i++)
        cout << "-";
    cout << "\n";
}
