// main.cpp
#include <iostream>
#include "ComplexNumber.h"
#include "sort_complex.h"

int main() {
    // Define the number of ComplexNumbers
    const int SIZE = 5;

    // Create an array of ComplexNumbers
    ComplexNumber complexArr[SIZE] = {
        ComplexNumber(3, 4),    // |3 + 4i| = 5
        ComplexNumber(1, 1),    // |1 + 1i| = sqrt(2)
        ComplexNumber(0, 2),    // |0 + 2i| = 2
        ComplexNumber(5, 12),   // |5 + 12i| = 13
        ComplexNumber(8, 15)    // |8 + 15i| = 17
    };

    // Display original array
    std::cout << "Original Complex Numbers:\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << complexArr[i] << " | Absolute Value: " << complexArr[i].abs() << "\n";
    }

    // Sort the array
    sortComplexNumbers(complexArr, SIZE);

    // Display sorted array
    std::cout << "\nSorted Complex Numbers (by absolute value):\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << complexArr[i] << " | Absolute Value: " << complexArr[i].abs() << "\n";
    }

    return 0;
}

