#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdexcept>
#include <iostream>
#include <string>

class Matrix {
    public:
        Matrix(int, int);
        Matrix(double**, int, int);
        Matrix(std::initializer_list<std::initializer_list<double>> values);
        Matrix();
        ~Matrix();
        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);

        inline double& operator()(int x, int y) { return p[x][y]; }

        class Proxy {
        public:
            explicit Proxy(double* row) : row_(row) {}
            inline double& operator[](int y) { return row_[y]; }
        private:
            double* row_;
        };

        inline Proxy operator[](int x) { return Proxy(p[x]); }

        Matrix& operator+=(const Matrix&);
        Matrix& operator-=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix& operator*=(double);
        Matrix& operator/=(const Matrix&);
        Matrix& operator/=(double);
        Matrix  operator^(int);
        
        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        friend std::istream& operator>>(std::istream&, Matrix&);

        void swapRows(int, int);
        Matrix transpose();

        static Matrix createIdentity(int);
        static Matrix solve(Matrix, Matrix);
        static Matrix bandSolve(Matrix, Matrix, int);

        // functions on vectors
        static double dotProduct(Matrix, Matrix);

        // functions on augmented matrices
        static Matrix augment(Matrix, Matrix);
        Matrix gaussianEliminate();
        Matrix rowReduceFromGaussian();
        void readSolutionsFromRREF(std::ostream& os);
        Matrix inverse();

        // get
        int getRows() const { return rows_; };
        int getCols() const { return cols_; };


    private:
        int rows_, cols_;
        double **p{};

        void allocSpace();
        Matrix expHelper(const Matrix&, int);
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, double);
Matrix operator/(double, const Matrix&);

// Function prototype

void check_broadcastable(const Matrix& m1, const Matrix& m2);

#endif