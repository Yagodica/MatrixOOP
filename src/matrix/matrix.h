#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Matrix {
    public:
        // Конструкторы
        Matrix(); // Конструктор по умолчанию
        Matrix(int, int); // Конструктор матрицы с заданным количеством строк и столбцов
        Matrix(double**, int, int); // Конструктор матрицы из двумерного массива
        Matrix(const Matrix&); // Копирующий конструктор
        Matrix(std::initializer_list<std::initializer_list<double>> values); // Конструктор матрицы из списка инициализации // TODO: изучить инит через = {}
        static Matrix fromVector(const std::vector<std::vector<double>>&, bool rowMajor = true); // Статический метод для создания матрицы из вектора // TODO: конверт из вектора

        ~Matrix(); // Деструктор

        inline double& operator()(int x, int y) { return p[x][y]; }

        class Proxy {
        public:
            explicit Proxy(double* row) : row_(row) {}
            inline double& operator[](int y) { return row_[y]; }
        private:
            double* row_;
        };

        inline Proxy operator[](int x) { return Proxy(p[x]); }

        // TODO: сравнение

        Matrix& operator=(const Matrix&);
        Matrix& operator+=(const Matrix&);
        Matrix& operator-=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix& operator*=(double);
        Matrix& operator/=(const Matrix&);
        Matrix& operator/=(double);
        Matrix  operator^(int); // Возведение в степень
        
        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        friend std::istream& operator>>(std::istream&, Matrix&);

        void swapRows(int, int);
        Matrix transpose();

        double determinant() const;

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
        Matrix inverse(); // Нахождение обратной матрицы

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