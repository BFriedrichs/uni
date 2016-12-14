#include <iostream>
#include <string.h>
#include <cfloat>

#include "matrix.hpp"

/**
 *  Allocates a matrix of desired size
 *
 * @param row - row count
 * @param col - col count
 */
Matrix::Matrix(float row, float col) : rowCount(row), colCount(col) {
    try {
        this->matrix = new float*[(unsigned int) row]();
    } catch(MatrixException& e) {
        throw MatrixException("Matrix could not be allocated");
    }

    for(unsigned int i = 0; i < row; i++) {
        try {
            this->matrix[i] = new float[(unsigned int) col]();
        } catch(MatrixException& e) {
            throw MatrixException("Matrix could not be allocated");
        }
    }
}

/**
 *  Copy constructor
 *
 * @param const Matrix &obj - matrix to copy
 */
Matrix::Matrix(const Matrix &obj) : rowCount(obj.rowCount), colCount(obj.colCount) {
    std::cout << "Ccot" << std::endl;
    try {
        this->matrix = new float*[(unsigned int) this->rowCount]();
    } catch(MatrixException& e) {
        throw MatrixException("Matrix could not be allocated");
    }

    for(unsigned int i = 0; i < this->rowCount; i++) {
        try {
            this->matrix[i] = new float[(unsigned int) this->colCount]();
            memcpy(this->matrix[i], obj.matrix[i], sizeof(float) * this->colCount);
        } catch(MatrixException& e) {
            throw MatrixException("Matrix could not be allocated");
        }
    }
}

/**
 * Matrix move constructor
 *
 * @param Matrix &&obj - Object to be moved
 */
Matrix::Matrix(Matrix &&obj) : rowCount(obj.rowCount), colCount(obj.colCount) {
    std::cout << "Mcot" << std::endl;
    this->matrix = obj.matrix;
    for(unsigned int i = 0; i < this->rowCount; i++) {
        this->matrix[i] = obj.matrix[i];
    }
    obj.matrix = NULL;
    obj.rowCount = obj.colCount = 0;
}

/**
 *  Matrix destructor
 */
Matrix::~Matrix() {
    for(unsigned int i = 0; i < this->rowCount; i++) {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}

/**
 *  Throws an exception if matrix isnt allocated
 */
void Matrix::checkAlloc(const Matrix *obj) const {
    if(this->matrix == NULL || obj != NULL && obj->matrix == NULL) {
        throw MatrixException("Matrix not allocated");
    }
}

/**
 * Matrix copy operator
 *
 * @param const Matrix &obj - Object to be copied
 * @return Matrix* - Pointer to the created object
 */
Matrix &Matrix::operator=(const Matrix &obj) {
    this->checkAlloc(&obj);
    std::cout << "op= copy" << std::endl;
    if(this != &obj) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;

        this->rowCount = obj.rowCount;
        this->colCount = obj.colCount;

        try {
            this->matrix = new float*[(unsigned int) this->rowCount]();
        } catch(MatrixException& e) {
            throw MatrixException("Matrix could not be allocated");
        }

        for(unsigned int i = 0; i < this->rowCount; i++) {
            try {
                this->matrix[i] = new float[(unsigned int) this->colCount]();
                memcpy(this->matrix[i], obj.matrix[i], sizeof(float) * this->colCount);
            } catch(MatrixException& e) {
                throw MatrixException("Matrix could not be allocated");
            }
        }
    }
    return *this;
}

/**
 * Matrix move operator
 *
 * @param Matrix &&obj - Object to be moved
 * @return Matrix* - Pointer to the created object
 */
Matrix &Matrix::operator=(Matrix &&obj) {
    this->checkAlloc(&obj);
    std::cout << "op= move" << std::endl;
    if(this != &obj) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;

        this->rowCount = obj.rowCount;
        this->colCount = obj.colCount;
        this->matrix = obj.matrix;

        for(unsigned int i = 0; i < this->rowCount; i++) {
            this->matrix[i] = obj.matrix[i];
        }

        obj.matrix = NULL;
        obj.rowCount = obj.colCount = 0;
    }

    return *this;
}

/**
 * Add operator for 2 matrix objects
 * Throws error if row and col count arent equal
 *
 * @param const Matrix &obj - Matrix object to add
 * @return Matrix - Matrix consisting of values of the 2 add matrices
 */

Matrix Matrix::operator+(const Matrix &obj) const {
    this->checkAlloc(&obj);
    std::cout << "op+" << std::endl;
    if(this->rowCount == obj.rowCount && this->colCount == obj.colCount) {
        Matrix result(this->rowCount, this->colCount);
        for(unsigned int i = 0; i < result.rowCount; i++) {
            for(unsigned int j = 0; j < result.colCount; j++) {
                result.matrix[i][j] = this->matrix[i][j] + obj.matrix[i][j];
            }
        }
        return result;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Add-Equals operator for 2 matrix objects
 * Throws error if row and col count arent equal
 *
 * @param const Matrix &obj - Matrix object to add
 * @return &Matrix - Reference to new Matrix object
 */
Matrix &Matrix::operator+=(const Matrix &obj) {
    this->checkAlloc(&obj);
    std::cout << "op+=" << std::endl;
    if(this->rowCount == obj.rowCount && this->colCount == obj.colCount) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            for(unsigned int j = 0; j < this->colCount; j++) {
                this->matrix[i][j] += obj.matrix[i][j];
            }
        }
        return *this;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Substract operator for 2 matrix objects
 * Throws error if row and col count arent equal
 *
 * @param const Matrix &obj - Matrix object to substract
 * @return Matrix - Matrix consisting of values of the 2 subtracted matrices
 */
Matrix Matrix::operator-(const Matrix &obj) const {
    this->checkAlloc(&obj);
    std::cout << "op-" << std::endl;
    if(this->rowCount == obj.rowCount && this->colCount == obj.colCount) {
        Matrix result(this->rowCount, this->colCount);
        for(unsigned int i = 0; i < result.rowCount; i++) {
            for(unsigned int j = 0; j < result.colCount; j++) {
                result.matrix[i][j] = this->matrix[i][j] - obj.matrix[i][j];
            }
        }
        return result;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Subtract-Equals operator for 2 matrix objects
 * Throws error if row and col count arent equal
 *
 * @param const Matrix &obj - Matrix object to substract
 * @return Matrix - Reference to new Matrix object
 */
Matrix &Matrix::operator-=(const Matrix &obj) {
    this->checkAlloc(&obj);
    std::cout << "op-=" << std::endl;
    if(this->rowCount == obj.rowCount && this->colCount == obj.colCount) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            for(unsigned int j = 0; j < this->colCount; j++) {
                this->matrix[i][j] -= obj.matrix[i][j];
            }
        }
        return *this;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Multiplication operator for 2 matrix objects
 * Throws error if col count isnt equal to other matrix' row count
 *
 * @param const Matrix &obj - Matrix object to multiply with
 * @return Matrix - Matrix with new bounds created from multiplication
 */
Matrix Matrix::operator*(const Matrix &obj) const {
    this->checkAlloc(&obj);
    std::cout << "op*" << std::endl;
    if(this->colCount == obj.rowCount) {
        Matrix result(this->rowCount, obj.colCount);
        for(unsigned int i = 0; i < result.rowCount; i++) {
            for(unsigned int j = 0; j < result.colCount; j++) {
                for(unsigned int k = 0; k < this->colCount; k++) {
                    result.matrix[i][j] += this->matrix[i][k] * obj.matrix[k][j];
                }
            }
        }
        return result;
    }

    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Add operator to add a scalar to the matrix
 * Throws error if its not a square matrix
 *
 * @param const float scalar - scalar to add to matrix
 * @return Matrix - New Matrix Object
 */
Matrix Matrix::operator+(const float scalar) const {
    this->checkAlloc();
    std::cout << "op+ scalar" << std::endl;
    if(this->rowCount == this->colCount) {
        Matrix result(this->rowCount, this->colCount);
        for(unsigned int i = 0; i < result.rowCount; i++) {
            result.matrix[i][i] = this->matrix[i][i] + scalar;
        }
        return result;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Add-Equals operator to add a scalar to a matrix
 * Throws error if its not a square matrix
 *
 * @param const float scalar - scalar to add to matrix
 * @return Matrix - Reference to new Matrix object
 */
Matrix &Matrix::operator+=(const float scalar) {
    this->checkAlloc();
    std::cout << "op+= scalar" << std::endl;
    if(this->rowCount == this->colCount) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            this->matrix[i][i] += scalar;
        }
        return *this;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Subtract operator to substract a scalar from the matrix
 * Throws error if its not a square matrix
 *
 * @param const float scalar - scalar to subtract from the matrix
 * @return Matrix - New Matrix Object
 */
Matrix Matrix::operator-(const float scalar) const {
    this->checkAlloc();
    std::cout << "op- scalar" << std::endl;
    if(this->rowCount == this->colCount) {
        Matrix result(this->rowCount, this->colCount);
        for(unsigned int i = 0; i < result.rowCount; i++) {
            result.matrix[i][i] = this->matrix[i][i] - scalar;
        }
        return result;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Subtract-Equals operator to subtract a scalar from a matrix
 * Throws error if its not a square matrix
 *
 * @param const float scalar - scalar to substract from the matrix
 * @return Matrix - Reference to new Matrix object
 */
Matrix &Matrix::operator-=(const float scalar) {
    this->checkAlloc();
    std::cout << "op-= scalar" << std::endl;
    if(this->rowCount == this->colCount) {
        for(unsigned int i = 0; i < this->rowCount; i++) {
            this->matrix[i][i] -= scalar;
        }
        return *this;
    }
    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Multiplication operator to multiply a matrix with a scalar
 *
 * @param const float scalar - scalar to multiply the matrix with
 * @return Matrix - New matrix object
 */
Matrix Matrix::operator*(const float scalar) const {
    this->checkAlloc();
    std::cout << "op* scalar" << std::endl;
    Matrix result(this->rowCount, this->colCount);
    for(unsigned int i = 0; i < this->rowCount; i++) {
        for(unsigned int j = 0; j < this->colCount; j++) {
            result.matrix[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return result;
}

/**
 * Multiplication-Equals operator to multiply a matrix with a scalar
 *
 * @param const float scalar - scalar to multiply the matrix with
 * @return Matrix - Reference to new Matrix object
 */
Matrix &Matrix::operator*=(const float scalar) {
    this->checkAlloc();
    std::cout << "op*= scalar" << std::endl;
    for(unsigned int i = 0; i < this->rowCount; i++) {
        for(unsigned int j = 0; j < this->colCount; j++) {
            this->matrix[i][j] *= scalar;
        }
    }
    return *this;
}

/**
 * Fills each cell of the matrix with the sum of its row and col value
 */
void Matrix::fill() {
    this->checkAlloc();
    for(unsigned int i = 0; i < this->rowCount; i++) {
        for(unsigned int j = 0; j < this->colCount; j++) {
            this->matrix[i][j] = i + j;
        }
    }
}

/**
 * Adds a value to the specified cell
 * Throws an error if row and col arent in the matrix bounds
 *
 * @param const float value - value to add to the cell
 * @param const float row - row in the matrix
 * @param const float col - col in the matrix
 */
void Matrix::addValue(const float value, const int row, const int col) {
    this->checkAlloc();
    if(row <= this->rowCount && col <= this->colCount) {
        if(this->matrix[row][col] + value <= FLT_MAX) {
            this->matrix[row][col] += value;
        }
    } else {
        throw MatrixException("Out of bounds");
    }
}

/**
 * Returns the determinant of the specified matrix if its a 2x2 or 3x3 matrix
 * Otherwise throws an error
 *
 * @return float - determinant of the matrix
 */
float Matrix::computeDeterminant() const {
    this->checkAlloc();
    if(this->rowCount == 2 && this->colCount == 2) {
        return this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
    }

    if(this->rowCount == 3 && this->colCount == 3) {
        return this->matrix[0][0] * this->matrix[1][1] * this->matrix[2][2] +
                this->matrix[0][1] * this->matrix[1][2] * this->matrix[2][0] +
                this->matrix[0][2] * this->matrix[1][0] * this->matrix[2][1] -
                this->matrix[0][2] * this->matrix[1][1] * this->matrix[2][0] -
                this->matrix[0][1] * this->matrix[1][0] * this->matrix[2][2] -
                this->matrix[0][0] * this->matrix[1][2] * this->matrix[2][1];
    }

    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Returns the inverse matrix as an object
 * Throws an error if the determinant is 0
 *
 * @return Matrix - inverse matrix object
 */
Matrix Matrix::computeInverse() const {
    this->checkAlloc();
    if(this->rowCount == 2 && this->colCount == 2) {
        float det = this->computeDeterminant();
        if(det == 0) {
            throw MatrixException("Determinant is 0");
        }
        det = 1 / det;

        // easy hard mapped for 2x2
        Matrix result(2, 2);
        result.matrix[0][0] = this->matrix[1][1];
        result.matrix[0][1] = -this->matrix[0][1];
        result.matrix[1][0] = -this->matrix[1][0];
        result.matrix[1][1] = this->matrix[0][0];

        return result * det;
    }

    if(this->rowCount == 3 && this->colCount == 3) {

        // first create transposed matrix
        Matrix trans = *this;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                trans.matrix[j][i] = this->matrix[i][j];
            }
        }

        // then get create the 2x2 matrix for every entry
        Matrix small[9] = {
            trans.getCutout(2,  (const float[]) {1, 1, 2, 2},       // a11
                                (const float[]) {1, 2, 1, 2} ),

            trans.getCutout(2,  (const float[]) {1, 1, 2, 2},       // a12
                                (const float[]) {0, 2, 0, 2} ),

            trans.getCutout(2,  (const float[]) {1, 1, 2, 2},       // a13
                                (const float[]) {0, 1, 0, 1} ),

            trans.getCutout(2,  (const float[]) {0, 0, 2, 2},       // a21
                                (const float[]) {1, 2, 1, 2} ),

            trans.getCutout(2,  (const float[]) {0, 0, 2, 2},       // a22
                                (const float[]) {0, 2, 0, 2} ),

            trans.getCutout(2,  (const float[]) {0, 0, 2, 2},       // a23
                                (const float[]) {0, 1, 0, 1} ),

            trans.getCutout(2,  (const float[]) {0, 0, 1, 1},       // a31
                                (const float[]) {1, 2, 1, 2} ),

            trans.getCutout(2,  (const float[]) {0, 0, 1, 1},       // a32
                                (const float[]) {0, 2, 0, 2} ),

            trans.getCutout(2,  (const float[]) {0, 0, 1, 1},       // a33
                                (const float[]) {0, 1, 0, 1} ),
        };

        // get the determinant for every one of these matrices
        Matrix cof(3, 3);
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cof.matrix[i][j] = small[i*3 + j].computeDeterminant();
            }
        }

        // create adjunct matrix
        cof.matrix[0][1] *= -1;
        cof.matrix[1][0] *= -1;
        cof.matrix[1][2] *= -1;
        cof.matrix[2][1] *= -1;

        float det = this->computeDeterminant();
        if(det == 0) {
            throw MatrixException("Determinant is 0");
        }
        det = 1 / det;

        // return new inversed matrix
        return cof * det;
    }

    throw MatrixException("Unsupported matrix dimensions");
}

/**
 * Returns a new matrix of the supplied size that represents a cutout of the supplied points.
 * Throws an error if a point is out of bounds of the current matrix
 *
 * @param const float size - size of the new matrix
 * @param const float rows[] - row coordinates of the supplied point
 * @param const float cols[] - col coordinates of the supplied point
 * @return float - determinant of the matrix
 */
Matrix Matrix::getCutout(const float size, const float rows[], const float cols[]) const {
    Matrix result(size, size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int row = rows[i*2 + j];
            int col = cols[i*2 + j];
            if(row >= this->rowCount || col >= this->colCount) {
                throw MatrixException("Point out of bounds");
            }

            result.matrix[i][j] = this->matrix[row][col];
        }
    }

    return result;
}

// Print the matrix
std::ostream& operator<<(std::ostream &os, const Matrix &obj) {
    for(unsigned int i = 0; i < obj.rowCount; i++) {
        for(unsigned int j = 0; j < obj.colCount; j++) {
            std::cout << obj.matrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    return os;
}
