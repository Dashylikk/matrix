#pragma once

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int numRows, int numCols);
    Matrix(const std::vector<std::vector<double>>& matrixData);
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator~() const;

    std::vector<double>& operator[](int rowIndex);
    const std::vector<double>& operator[](int rowIndex) const;

    bool isEmpty() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

private:
    bool haveSameSize(const Matrix& other) const;
};
