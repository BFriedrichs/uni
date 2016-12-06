#include <exception>
#include <string>

#ifndef MATRIX_H
#define MATRIX_H

class MatrixException : public std::exception {
    protected:
        std::string error;

    public:
        explicit MatrixException(const char *error) : error(error) {}
        virtual const char *what() const throw() { return error.c_str(); }
};

class Matrix {
    private:
        float **matrix;
        float rowCount;
        float colCount;
        void checkAlloc(const Matrix *obj=NULL) const;
        Matrix getCutout(const float size, const float rows[], const float cols[]) const;

    public:
        Matrix(float row, float col);
        Matrix(const Matrix &obj);
        Matrix(Matrix &&obj);
        ~Matrix();

        Matrix &operator=(const Matrix &obj);
        Matrix &operator=(Matrix &&obj);

        Matrix operator+(const Matrix &obj) const;
        Matrix &operator+=(const Matrix &obj);
        Matrix operator-(const Matrix &obj) const;
        Matrix &operator-=(const Matrix &obj);
        Matrix operator*(const Matrix &obj) const;

        Matrix operator+(const float scalar) const;
        Matrix &operator+=(const float scalar);
        Matrix operator-(const float scalar) const;
        Matrix &operator-=(const float scalar);
        Matrix operator*(const float scalar) const;
        Matrix &operator*=(const float scalar);

        Matrix computeInverse() const;
        void fill();
        void addValue(const float value, const int row, const int col);
        float computeDeterminant() const;

    friend std::ostream& operator<<(std::ostream &os, const Matrix &obj);
};

std::ostream& operator<<(std::ostream &os, const Matrix &obj);

#endif