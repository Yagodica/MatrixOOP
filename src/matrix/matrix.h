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
        Matrix(std::initializer_list<std::initializer_list<double>> values); // Конструктор матрицы из списка инициализации
        static Matrix fromVector(const std::vector<std::vector<double>>&, bool rowMajor = true); // Статический метод для создания матрицы из вектора

        ~Matrix(); // Деструктор

        inline double& operator()(int x, int y) { return p[x][y]; } // оператор индексирования ()

        class Proxy { // Необходим для итерации по строке
            public:
                explicit Proxy(double* row) : row_(row) {}
                inline double& operator[](int y) { return row_[y]; }
            private:
                double* row_;
        };

        inline Proxy operator[](int x) { return Proxy(p[x]); } // оператор индексирования []

        bool operator==(const Matrix&) const;       // оператор равенства
        bool operator!=(const Matrix& other) const; // оператор неравенства

        Matrix& operator=(const Matrix&);   // оператор присваивания
        Matrix& operator+=(const Matrix&);  // сложение матриц
        Matrix& operator-=(const Matrix&);  // вычитание матриц
        Matrix& operator*=(const Matrix&);  // умножение матриц
        Matrix& operator*=(double);         // умножение матрицы на скаляр
        Matrix& operator/=(const Matrix&);  // деление матриц
        Matrix& operator/=(double);         // деление матрицы на скаляр
        Matrix  operator^(int);             // возведение матрицы в степень

        friend std::ostream& operator<<(std::ostream&, const Matrix&);  // перегрузка оператора << для вывода матрицы
        friend std::istream& operator>>(std::istream&, Matrix&);        // перегрузка оператора >> для ввода матрицы

        void swapRows(int, int);    // поменять строки
        Matrix transpose();         // транспонирование матрицы

        double determinant() const; // вычисление определителя матрицы

        static Matrix createIdentity(int);              // создание единичной матрицы
        static Matrix solve(Matrix, Matrix);            // решает систему линейных уравнений методом Гаусса с обратной подстановкой

        // функции на векторах
        static double dotProduct(Matrix, Matrix);       // скалярное произведение векторов

        // функции над расширенными матрицами
        static Matrix augment(Matrix&, Matrix&);        // объединение матриц в расширенную матрицу
        Matrix gaussianEliminate();                     // преобразование матрицы в ступенчатый вид
        Matrix gaussianEliminate2();                    // преобразование матрицы в ступенчатый вид // TODO: Кал
        Matrix rowReduceFromGaussian();                 // сокращение матрицы до редуцированного ступенчатого вида
        Matrix inverse();                               // нахождение обратной матрицы

        // get
        int getRows() const { return rows_; };
        int getCols() const { return cols_; };

        // Полезное
        static Matrix randomMatrix(int, int, int, int);
        static Matrix zeroMatrix(int, int);
        Matrix removeColumns(int, int);

private:
        int rows_, cols_;
        double **p{};

        void allocSpace();                      // выделение памяти под матрицу
        Matrix expHelper(const Matrix&, int);   // вспомогательная функция для возведения матрицы в степень
};

Matrix operator+(const Matrix&, const Matrix&); // сложение матриц
Matrix operator-(const Matrix&, const Matrix&); // вычитание матриц
Matrix operator*(const Matrix&, const Matrix&); // умножение матриц
Matrix operator*(const Matrix&, double);        // умножение матрицы на скаляр
Matrix operator*(double, const Matrix&);        // умножение скаляра на матрицу
Matrix operator/(const Matrix&, const Matrix&); // деление матрицы на матрицу
Matrix operator/(const Matrix&, double);        // деление матрицы на скаляр


// Function prototype

void check_broadcastable(const Matrix& m1, const Matrix& m2); // проверка соответствия размерностей матриц

#endif