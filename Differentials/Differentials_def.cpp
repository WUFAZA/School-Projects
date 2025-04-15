#include "Differentials.h"
#include <iostream>
#include <string>

using namespace std;
// Single-variable analysis
void analyzeSingleVariable() {
    double coeffDerivative, coeffY, constant;

    // Ask for coefficients of dy/dx, y, and constant term
    cout << "For single-variable equations, enter the coefficients of each term.\n";
    cout << "Coefficient of dy/dx: ";
    cin >> coeffDerivative;
    cout << "Coefficient of y: ";
    cin >> coeffY;
    cout << "Constant term: ";
    cin >> constant;

    // Analyze linearity and homogeneity
    if (constant == 0) {
        cout << "- The equation is Homogeneous.\n";
    }
    else {
        cout << "- The equation is Non-homogeneous.\n";
    }

    if (coeffY != 0) {
        cout << "- The equation is Linear.\n";
    }
    else {
        cout << "- The equation is Non-linear.\n";
    }
}

// Multivariable analysis
void analyzeMultivariable() {
    std::string m, n;

    // Ask for M(x, y) and N(x, y)
    cout << "For multivariable equations, enter the components of the equation.\n";
    cout << "M(x, y): ";
    cin.ignore(); // Clear buffer
    getline(std::cin, m);
    cout << "N(x, y): ";
    getline(std::cin, n);

    // Simplistic check for exactness
    cout << "Note: Exactness requires ∂M/∂y = ∂N/∂x (not automatically verified).\n";
    cout << "- Make sure to check partial derivatives for exactness.\n";
}

// Main equation analyzer
void analyzeEquation() {
    int choice;
    cout << "Do you want to analyze a single-variable or multivariable equation?\n";
    cout << "Enter 1 for single-variable, 2 for multivariable: ";
    cin >> choice;

    if (choice == 1) {
        analyzeSingleVariable();
    }
    else if (choice == 2) {
        analyzeMultivariable();
    }
    else {
        cout << "Invalid choice. Please restart the program.\n";
    }
}
