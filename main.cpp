#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include "Matrix.h"


int main() {
    int numRowsA, numColsA, numRowsB, numColsB;

    do {
        std::cout << "Enter rows and column of matrix A (e.g., 2 2): ";
        std::string inputA;
        std::getline(std::cin, inputA);

        std::stringstream streamA(inputA);
        streamA >> numRowsA >> numColsA;

        if (streamA.fail() || streamA.peek() != EOF) {
            std::cout << "Invalid input. Please enter two valid numbers separated by a space." << std::endl;
            streamA.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
        }
        else {
            break;  // Exit the loop if input is valid
        }
    } while (true);

    // ��������� ������� A
    Matrix A(numRowsA, numColsA);
    std::cout << "Enter matrix A data:" << std::endl;
    std::cin >> A;
    std::cin.ignore(); // ��� �������� �������� � ����������� ���������� �����

    std::cout << "Matrix A:" << std::endl;
    std::cout << A << std::endl;

    std::cout << "Enter rows and column of matrix B: ";
    std::string inputB;
    std::getline(std::cin, inputB);

    std::stringstream streamB(inputB);
    streamB >> numRowsB >> numColsB;

    // ��������� ������� B
    Matrix B(numRowsB, numColsB);
    std::cout << "Enter matrix B data:" << std::endl;
    std::cin >> B;
    std::cin.ignore(); // ��� �������� �������� � ����������� ���������� �����

    std::cout << "Matrix B:" << std::endl;
    std::cout << B << std::endl;

    bool invalidOperation = false;
    bool additionPossible = (numRowsA == numRowsB && numColsA == numColsB);
    bool multiplicationPossible = (numColsA == numRowsB);

    do {
        if (invalidOperation) {
            std::cout << "Invalid operation. Please enter a valid operation or 'exit' to quit." << std::endl;
            invalidOperation = false;
        }

        std::string operation;
        std::cout << "Enter an operation to perform ( A + B, B - A, A = B, A == B, B * 2, A tr, exit to quit): ";
        std::getline(std::cin, operation);

        if (operation == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        if ((operation == "A + B" || operation == "A - B" || operation == "B - A") && !additionPossible) {
            std::cout << "Matrices A and B must have the same dimensions for addition/subtraction!" << std::endl;
            continue;
        }
        else if ((operation == "A * B" || operation == "B * A") && !multiplicationPossible) {
            std::cout << "Matrices A and B dimensions are incompatible for multiplication!" << std::endl;
            continue;
        }

        Matrix result;
        if (operation == "A + B") {
            result = A + B;
        }
        else if (operation == "A = B") {
            if (numRowsA == numRowsB && numColsA == numColsB) {
                A = B;
            }
            else {
                std::cout << "Matrices have different dimensions and cannot be assigned." << std::endl;
            }
        }
        else if (operation == "B = A") {
            if (numRowsB == numRowsA && numColsB == numColsA) {
                B = A;
            }
            else {
                std::cout << "Matrices have different dimensions and cannot be assigned." << std::endl;
            }
        }
        else if (operation == "A == B") {
            bool areEqual = (A == B);
            std::cout << "Matrix A is " << (areEqual ? "equal" : "not equal") << " to Matrix B." << std::endl;
        }
        else if (operation == "A - B") {
            result = A - B;
        }
        else if (operation == "B - A") {
            result = B - A;
        }
        else if (operation == "A * B") {
            result = A * B;
        }
        else if (operation == "B * A") {
            result = B * A;
        }
        else if (operation == "A tr") {
            result = ~A;
        }
        else if (operation == "B tr") {
            result = ~B;
        }
        else if (operation.find("A * ") == 0) {
            double scalar = std::stod(operation.substr(4));
            result = A * scalar;
        }
        else if (operation.find("B * ") == 0) {
            double scalar = std::stod(operation.substr(4));
            result = B * scalar;
        }
        else {
            invalidOperation = true;
            continue;
        }

        if (!result.isEmpty()) {
            std::cout << "Result of the operation (" << operation << "):" << std::endl;
            std::cout << result << std::endl;
        }
    } while (true);

    return 0;
}
