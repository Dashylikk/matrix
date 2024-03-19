#include "Matrix.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <limits>

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& matrixData) {
    if (matrixData.empty() || matrixData[0].empty()) {
        rows = 0;
        cols = 0;
    }
    else {
        rows = matrixData.size();
        cols = matrixData[0].size();
        data = matrixData;
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    return (rows == other.rows && cols == other.cols && data == other.data);
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (!haveSameSize(other)) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (!haveSameSize(other)) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator~() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

std::vector<double>& Matrix::operator[](int rowIndex) {
    if (rowIndex < 0 || rowIndex >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    return data[rowIndex];
}

const std::vector<double>& Matrix::operator[](int rowIndex) const {
    if (rowIndex < 0 || rowIndex >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    return data[rowIndex];
}

bool Matrix::isEmpty() const {
    return rows == 0 && cols == 0;
}

bool Matrix::haveSameSize(const Matrix& other) const {
    return rows == other.rows && cols == other.cols;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            os << std::setw(8) << std::fixed << std::setprecision(2) << matrix.data[i][j];
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    std::cout << "Enter matrix data row by row:" << std::endl;
    for (int i = 0; i < matrix.rows; ++i) {
        std::vector<double> row;
        std::cout << "Enter " << matrix.cols << " values for row " << i + 1 << ": ";
        for (int j = 0; j < matrix.cols; ++j) {
            double value;
            is >> value;
            row.push_back(value);
        }
        matrix.data[i] = row;
    }
    return is;
}
