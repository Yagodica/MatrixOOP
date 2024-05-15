#include "src/matrix/matrix.h"
#include "gtest/gtest.h"

// Тестирование конструктора по умолчанию и конструктора с параметрами
TEST(MatrixTest, Constructors) {
    Matrix m1;
    EXPECT_EQ(m1.getRows(), 1);
    EXPECT_EQ(m1.getCols(), 1);

    Matrix m2(3, 4);
    EXPECT_EQ(m2.getRows(), 3);
    EXPECT_EQ(m2.getCols(), 4);
}

// Тестирование оператора присваивания
TEST(MatrixTest, AssignmentOperator) {
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;

    Matrix m2 = m1;

    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m2(1, 0), 3);
    EXPECT_EQ(m2(1, 1), 4);
}

// Тестирование оператора сложения
TEST(MatrixTest, AdditionOperator) {
    Matrix m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;

    Matrix m2(2, 2);
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;

    Matrix m3 = m1 + m2;

    EXPECT_EQ(m3(0, 0), 6);
    EXPECT_EQ(m3(0, 1), 8);
    EXPECT_EQ(m3(1, 0), 10);
    EXPECT_EQ(m3(1, 1), 12);
}

// Тестирование оператора () (индексирования)
TEST(MatrixTest, OperatorParentheses) {
    Matrix matrix(3, 3);
    matrix(0, 0) = 1;
    matrix(1, 1) = 2;
    matrix(2, 2) = 3;

    EXPECT_EQ(matrix(0, 0), 1);
    EXPECT_EQ(matrix(1, 1), 2);
    EXPECT_EQ(matrix(2, 2), 3);
}

// Тестирование оператора [] (индексирования)
TEST(MatrixTest, OperatorBrackets) {
    Matrix matrix(3, 3);
    matrix[0][0] = 1;
    matrix[1][1] = 2;
    matrix[2][2] = 3;

    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[1][1], 2);
    EXPECT_EQ(matrix[2][2], 3);
}

// Тестирование оператора == (равно)
TEST(MatrixTest, OperatorEqual) {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1(0, 0) = 1;
    matrix1(1, 1) = 2;
    matrix1(2, 2) = 3;

    matrix2(0, 0) = 1;
    matrix2(1, 1) = 2;
    matrix2(2, 2) = 3;

    EXPECT_TRUE(matrix1 == matrix2);
}

// Тестирование оператора != (не равно)
TEST(MatrixTest, OperatorNotEqual) {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1(0, 0) = 1;
    matrix1(1, 1) = 2;
    matrix1(2, 2) = 3;

    matrix2(0, 0) = 1;
    matrix2(1, 1) = 2;
    matrix2(2, 2) = 4;

    EXPECT_TRUE(matrix1 != matrix2);
}

// Тестирование оператора += (сложение с присваиванием)
TEST(MatrixTest, OperatorPlusAssign) {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1(0, 0) = 1;
    matrix1(1, 1) = 2;
    matrix1(2, 2) = 3;

    matrix2(0, 0) = 1;
    matrix2(1, 1) = 2;
    matrix2(2, 2) = 3;

    matrix1 += matrix2;

    EXPECT_EQ(matrix1(0, 0), 2);
    EXPECT_EQ(matrix1(1, 1), 4);
    EXPECT_EQ(matrix1(2, 2), 6);
}

// Тестирование оператора -= (вычитание с присваиванием)
TEST(MatrixTest, OperatorMinusAssign) {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1(0, 0) = 3;
    matrix1(1, 1) = 4;
    matrix1(2, 2) = 5;

    matrix2(0, 0) = 1;
    matrix2(1, 1) = 2;
    matrix2(2, 2) = 3;

    matrix1 -= matrix2;

    EXPECT_EQ(matrix1(0, 0), 2);
    EXPECT_EQ(matrix1(1, 1), 2);
    EXPECT_EQ(matrix1(2, 2), 2);
}

// Тестирование оператора *= (умножение с присваиванием)
TEST(MatrixTest, OperatorMultiplyAssign) {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);

    matrix1(0, 0) = 1;
    matrix1(0, 1) = 2;
    matrix1(0, 2) = 3;
    matrix1(1, 0) = 4;
    matrix1(1, 1) = 5;
    matrix1(1, 2) = 6;
    matrix1(2, 0) = 7;
    matrix1(2, 1) = 8;
    matrix1(2, 2) = 9;

    matrix2(0, 0) = 9;
    matrix2(0, 1) = 8;
    matrix2(0, 2) = 7;
    matrix2(1, 0) = 6;
    matrix2(1, 1) = 5;
    matrix2(1, 2) = 4;
    matrix2(2, 0) = 3;
    matrix2(2, 1) = 2;
    matrix2(2, 2) = 1;

    matrix1 *= matrix2;

    EXPECT_EQ(matrix1(0, 0), 30);
    EXPECT_EQ(matrix1(0, 1), 24);
    EXPECT_EQ(matrix1(0, 2), 18);
    EXPECT_EQ(matrix1(1, 0), 84);
    EXPECT_EQ(matrix1(1, 1), 69);
    EXPECT_EQ(matrix1(1, 2), 54);
    EXPECT_EQ(matrix1(2, 0), 138);
    EXPECT_EQ(matrix1(2, 1), 114);
    EXPECT_EQ(matrix1(2, 2), 90);
}

// Тестирование оператора /= (деление с присваиванием)
TEST(MatrixTest, OperatorDivideAssign) {
    Matrix matrix(3, 3);

    matrix(0, 0) = 2;
    matrix(1, 1) = 3;
    matrix(2, 2) = 4;

    matrix /= 2;

    EXPECT_FLOAT_EQ(matrix(0, 0), 1);
    EXPECT_FLOAT_EQ(matrix(1, 1), 1.5);
    EXPECT_FLOAT_EQ(matrix(2, 2), 2);
}

// Тестирование транспонирования матрицы
TEST(MatrixTest, Transpose) {
    Matrix matrix(3, 3);

    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(0, 2) = 3;
    matrix(1, 0) = 4;
    matrix(1, 1) = 5;
    matrix(1, 2) = 6;
    matrix(2, 0) = 7;
    matrix(2, 1) = 8;
    matrix(2, 2) = 9;

    Matrix transposedMatrix = matrix.transpose();

    EXPECT_EQ(transposedMatrix(0, 0), 1);
    EXPECT_EQ(transposedMatrix(0, 1), 4);
    EXPECT_EQ(transposedMatrix(0, 2), 7);
    EXPECT_EQ(transposedMatrix(1, 0), 2);
    EXPECT_EQ(transposedMatrix(1, 1), 5);
    EXPECT_EQ(transposedMatrix(1, 2), 8);
    EXPECT_EQ(transposedMatrix(2, 0), 3);
    EXPECT_EQ(transposedMatrix(2, 1), 6);
    EXPECT_EQ(transposedMatrix(2, 2), 9);
}

// Тестирование вычисления определителя матрицы
TEST(MatrixTest, Determinant) {
    Matrix matrix2x2(2, 2);
    matrix2x2(0, 0) = 4;
    matrix2x2(0, 1) = 1;
    matrix2x2(1, 0) = 3;
    matrix2x2(1, 1) = 2;

    EXPECT_FLOAT_EQ(matrix2x2.determinant(), 5);

    Matrix matrix3x3(3, 3);
    matrix3x3(0, 0) = 1;
    matrix3x3(0, 1) = 2;
    matrix3x3(0, 2) = 3;
    matrix3x3(1, 0) = 4;
    matrix3x3(1, 1) = 5;
    matrix3x3(1, 2) = 6;
    matrix3x3(2, 0) = 7;
    matrix3x3(2, 1) = 8;
    matrix3x3(2, 2) = 9;

    EXPECT_FLOAT_EQ(matrix3x3.determinant(), 0);
}

// Тестирование создания единичной матрицы
TEST(MatrixTest, CreateIdentity) {
    Matrix identityMatrix = Matrix::createIdentity(3);

    EXPECT_EQ(identityMatrix(0, 0), 1);
    EXPECT_EQ(identityMatrix(0, 1), 0);
    EXPECT_EQ(identityMatrix(0, 2), 0);
    EXPECT_EQ(identityMatrix(1, 0), 0);
    EXPECT_EQ(identityMatrix(1, 1), 1);
    EXPECT_EQ(identityMatrix(1, 2), 0);
    EXPECT_EQ(identityMatrix(2, 0), 0);
    EXPECT_EQ(identityMatrix(2, 1), 0);
    EXPECT_EQ(identityMatrix(2, 2), 1);
}

// Тестирование решения системы линейных уравнений // TODO: Починка
//TEST(MatrixTest, Solve) {
//    Matrix A(3, 3);
//    Matrix b(3, 1);
//
//    A(0, 0) = 3;
//    A(0, 1) = 2;
//    A(0, 2) = -1;
//    A(1, 0) = 2;
//    A(1, 1) = -2;
//    A(1, 2) = 4;
//    A(2, 0) = -1;
//    A(2, 1) = 0.5;
//    A(2, 2) = -1;
//
//    b(0, 0) = -3;
//    b(1, 0) = -2;
//    b(2, 0) = -1;
//
//    Matrix x = Matrix::solve(A, b);
//
//    EXPECT_FLOAT_EQ(x(0, 0), 1);
//    EXPECT_FLOAT_EQ(x(1, 0), -2);
//    EXPECT_FLOAT_EQ(x(2, 0), -1);
//}

// Тестирование скалярного произведения векторов
TEST(MatrixTest, DotProduct) {
    Matrix vector1(3, 1);
    Matrix vector2(3, 1);

    vector1(0, 0) = 1;
    vector1(1, 0) = 2;
    vector1(2, 0) = 3;

    vector2(0, 0) = 4;
    vector2(1, 0) = 5;
    vector2(2, 0) = 6;

    EXPECT_FLOAT_EQ(Matrix::dotProduct(vector1, vector2), 32);
}

// Тестирование объединения матриц в расширенную матрицу
TEST(MatrixTest, Augment) {
    Matrix A(3, 3);
    Matrix B(3, 2);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;

    B(0, 0) = 10; B(0, 1) = 11;
    B(1, 0) = 12; B(1, 1) = 13;
    B(2, 0) = 14; B(2, 1) = 15;

    Matrix AB = Matrix::augment(A, B);

    EXPECT_EQ(AB(0, 0), 1);
    EXPECT_EQ(AB(0, 1), 2);
    EXPECT_EQ(AB(0, 2), 3);
    EXPECT_EQ(AB(0, 3), 10);
    EXPECT_EQ(AB(0, 4), 11);
    EXPECT_EQ(AB(1, 0), 4);
    EXPECT_EQ(AB(1, 1), 5);
    EXPECT_EQ(AB(1, 2), 6);
    EXPECT_EQ(AB(1, 3), 12);
    EXPECT_EQ(AB(1, 4), 13);
    EXPECT_EQ(AB(2, 0), 7);
    EXPECT_EQ(AB(2, 1), 8);
    EXPECT_EQ(AB(2, 2), 9);
    EXPECT_EQ(AB(2, 3), 14);
    EXPECT_EQ(AB(2, 4), 15);
}

// Тестирование преобразования матрицы в ступенчатый вид
TEST(MatrixTest, GaussianEliminate) {
    Matrix A(3, 4);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(0, 3) = 4;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;

    Matrix rowEchelonForm = A.gaussianEliminate();

    EXPECT_FLOAT_EQ(rowEchelonForm(0, 0), 1);
    EXPECT_FLOAT_EQ(rowEchelonForm(0, 1), 2);
    EXPECT_FLOAT_EQ(rowEchelonForm(0, 2), 3);
    EXPECT_FLOAT_EQ(rowEchelonForm(0, 3), 4);
    EXPECT_FLOAT_EQ(rowEchelonForm(1, 0), 0);
    EXPECT_FLOAT_EQ(rowEchelonForm(1, 1), -3);
    EXPECT_FLOAT_EQ(rowEchelonForm(1, 2), -6);
    EXPECT_FLOAT_EQ(rowEchelonForm(1, 3), -9);
    EXPECT_FLOAT_EQ(rowEchelonForm(2, 0), 0);
    EXPECT_FLOAT_EQ(rowEchelonForm(2, 1), 0);
    EXPECT_FLOAT_EQ(rowEchelonForm(2, 2), 0);
    EXPECT_FLOAT_EQ(rowEchelonForm(2, 3), 0);
}

// Тестирование сокращения матрицы до редуцированного ступенчатого вида
TEST(MatrixTest, RowReduceFromGaussian) {
    Matrix A(3, 4);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(0, 3) = 4;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(1, 3) = 7;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;
    A(2, 3) = 10;

    Matrix rowReducedEchelonForm = A.gaussianEliminate().rowReduceFromGaussian();

    EXPECT_FLOAT_EQ(rowReducedEchelonForm(0, 0), 1);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(0, 1), 2);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(0, 2), 3);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(0, 3), 4);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(1, 0), 0);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(1, 1), 1);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(1, 2), 2);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(1, 3), 3);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(2, 0), 0);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(2, 1), 0);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(2, 2), 0);
    EXPECT_FLOAT_EQ(rowReducedEchelonForm(2, 3), 0);
}

// Тестирование нахождения обратной матрицы
TEST(MatrixTest, Inverse) {
    Matrix A(3, 3);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;
    A(2, 0) = 7;
    A(2, 1) = 8;
    A(2, 2) = 9;

    Matrix AInverse = A.inverse();

    Matrix product = A * AInverse;

    EXPECT_FLOAT_EQ(product(0, 0), 1);
    EXPECT_FLOAT_EQ(product(0, 1), 0);
    EXPECT_FLOAT_EQ(product(0, 2), 0);
    EXPECT_FLOAT_EQ(product(1, 0), 0);
    EXPECT_FLOAT_EQ(product(1, 1), 1);
    EXPECT_FLOAT_EQ(product(1, 2), 0);
    EXPECT_FLOAT_EQ(product(2, 0), 0);
    EXPECT_FLOAT_EQ(product(2, 1), 0);
    EXPECT_FLOAT_EQ(product(2, 2), 1);
}

// Тестирование создания случайной матрицы
TEST(MatrixTest, RandomMatrix) {
    Matrix randomMatrix = Matrix::randomMatrix(3, 4, -10, 10);

    for (int i = 0; i < randomMatrix.getRows(); ++i) {
        for (int j = 0; j < randomMatrix.getCols(); ++j) {
            EXPECT_GE(randomMatrix(i, j), -10);
            EXPECT_LE(randomMatrix(i, j), 10);
        }
    }
}

// Тестирование создания нулевой матрицы
TEST(MatrixTest, ZeroMatrix) {
    Matrix zeroMatrix = Matrix::zeroMatrix(3, 4);

    for (int i = 0; i < zeroMatrix.getRows(); ++i) {
        for (int j = 0; j < zeroMatrix.getCols(); ++j) {
            EXPECT_EQ(zeroMatrix(i, j), 0);
        }
    }
}

// Тестирование удаления столбцов матрицы
TEST(MatrixTest, RemoveColumns) {
    Matrix A(3, 5);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;
    A(0, 3) = 4;
    A(0, 4) = 5;
    A(1, 0) = 6;
    A(1, 1) = 7;
    A(1, 2) = 8;
    A(1, 3) = 9;
    A(1, 4) = 10;
    A(2, 0) = 11;
    A(2, 1) = 12;
    A(2, 2) = 13;
    A(2, 3) = 14;
    A(2, 4) = 15;

    Matrix C = A.removeColumns(1, 3);

    EXPECT_EQ(C(0, 0), 1);
    EXPECT_EQ(C(0, 1), 5);
    EXPECT_EQ(C(1, 0), 6);
    EXPECT_EQ(C(1, 1), 10);
    EXPECT_EQ(C(2, 0), 11);
    EXPECT_EQ(C(2, 1), 15);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
