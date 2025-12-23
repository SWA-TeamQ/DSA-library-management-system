#include <iostream>
#include <iomanip>
#include <string>
#include "dsa/Array.hpp"

using namespace std;

void Row(const Array<string>& values, int width = 15) {
    for (int i = 0; i < values.size(); i++) {
        cout << "| " << left << setw(width) << values[i] << " ";
    }
    cout << "|\n";

    int totalWidth = values.size() * (width + 3) + 1;
    for (int i = 0; i < totalWidth; i++)
        cout << "-";
    cout << "\n";
}
