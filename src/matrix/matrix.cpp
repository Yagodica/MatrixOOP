#include "matrix.h"

#define EPS 1e-10

using std::ostream;
using std::istream;
using std::endl;
using std::domain_error;

// PUBLIC MEMBER FUNCTIONS

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = 0;
        }
    }
}

Matrix::Matrix(double** a, int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values) : rows_(values.size()), cols_(values.begin()->size()) {
    allocSpace();
    int i = 0;
    for (const auto& row : values) {
        int j = 0;
        for (const auto& value : row) {
            p[i][j] = value;
            j++;
        }
        i++;
    }
}

Matrix Matrix::fromVector(const std::vector<std::vector<double>>& vec, bool rowMajor) {
    int rows = vec.size();
    int cols = vec[0].size();

    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Invalid vector for matrix conversion");
    }

    Matrix mat(rows, cols);

    if (rowMajor) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat(i, j) = vec[i][j];
            }
        }
    } else {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat(j, i) = vec[i][j];
            }
        }
    }

    return mat;
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (p[i][j] != other.p[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}


Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] p[i];
        }
        delete[] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if (rows_ != m.rows_ || cols_ != m.cols_) {
        check_broadcastable(*this, m);
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
    if (rows_ != m.rows_ || cols_ != m.cols_) {
        check_broadcastable(*this, m);
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
    if (cols_ != m.rows_ || rows_ != m.cols_) {
        check_broadcastable(*this, m);
    }

    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                temp.p[i][j] += (p[i][k] * m.p[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix& Matrix::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] *= num;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const Matrix& m)
{
    Matrix temp(m);

    return (*this *= temp.inverse());
}

Matrix& Matrix::operator/=(double num)
{
    if (num == 0) {
        throw std::invalid_argument("Division by zero");
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] /= num;
        }
    }
    return *this;
}

Matrix Matrix::operator^(int num)
{
    Matrix temp(*this);
    return expHelper(temp, num);
}

void Matrix::swapRows(int r1, int r2)
{
    double *temp = p[r1];
    p[r1] = p[r2];
    p[r2] = temp;
}

Matrix Matrix::transpose()
{
    Matrix ret(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}

double Matrix::determinant() const { // Вычисление определителя
    if (rows_ != cols_) {
        throw std::runtime_error("matrix is not square, cannot compute determinant");
    }

    if (rows_ == 1) {
        return p[0][0];
    } else if (rows_ == 2) {
        return (p[0][0] * p[1][1]) - (p[0][1] * p[1][0]);
    } else {
        double det = 0;
        for (int i = 0; i < cols_; ++i) {
            Matrix submatrix(rows_ - 1, cols_ - 1);

            for (int j = 1; j < rows_; ++j) {
                int submatrixCol = 0;
                for (int k = 0; k < cols_; ++k) {
                    if (k != i) {
                        submatrix(j - 1, submatrixCol++) = p[j][k];
                    }
                }
            }

            det += std::pow(-1, i) * p[0][i] * submatrix.determinant();
        }
        return det;
    }
}


// STATIC CLASS FUNCTIONS

Matrix Matrix::createIdentity(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            if (i == j) {
                temp.p[i][j] = 1;
            } else {
                temp.p[i][j] = 0;
            }
        }
    }
    return temp;
}


double Matrix::sum() {
    double result{};
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result += p[i][j];
        }
    }
    return result;
}

Matrix Matrix::solve(Matrix A, Matrix b) {
    int n = A.getRows();
    if (n != A.getCols() || n != b.getRows()) {
        throw std::invalid_argument("Invalid dimensions");
    }

    Matrix aug = Matrix::augment(A, b);

    for (int i = 0; i < n; ++i) {
        int max_row = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(aug[j][i]) > std::abs(aug[max_row][i])) {
                max_row = j;
            }
        }
        if (i != max_row) {
            aug.swapRows(i, max_row);
        }

        if (aug[i][i] == 0) {
            throw std::runtime_error("Division by zero");
        }

        for (int j = i + 1; j < n; ++j) {
            double factor = aug[j][i] / aug[i][i];
            for (int k = i; k <= n; ++k) {
                aug[j][k] -= factor * aug[i][k];
            }
        }
    }

    Matrix x(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        x[i][0] = aug[i][n];
        for (int j = i + 1; j < n; ++j) {
            x[i][0] -= aug[i][j] * x[j][0];
        }
        x[i][0] /= aug[i][i];

        if (std::abs(x[i][0]) < EPS) {
            x[i][0] = 0;
        }
    }

    return x;
}

// функции на векторах
double Matrix::dotProduct(Matrix a, Matrix b)
{
    double sum = 0;
    for (int i = 0; i < a.rows_; ++i) {
        sum += (a(i, 0) * b(i, 0));
    }
    return sum;
}

// функции над расширенными матрицами
Matrix Matrix::augment(Matrix& A, Matrix& B) // Увеличение матрицы
{
    if (A.rows_ != B.rows_) {
        throw std::invalid_argument("Matrices must have the same number of rows");
    }

    Matrix AB(A.rows_, A.cols_ + B.cols_);
    for (int i = 0; i < AB.rows_; ++i) {
        for (int j = 0; j < AB.cols_; ++j) {
            if (j < A.cols_) {
                AB(i, j) = A(i, j);
            }
            else {
                AB(i, j) = B(i, j - A.cols_);
            }
        }
    }
    return AB;
}

Matrix Matrix::gaussianEliminate()
{
    Matrix Ab(*this);
    int rows = Ab.rows_;
    int cols = Ab.cols_;
    int Acols = cols - 1;

    int i = 0; // row tracker
    int j = 0; // column tracker

    // iterate through the rows
    while (i < rows)
    {
        // find a pivot for the row
        bool pivot_found = false;
        while (j < Acols && !pivot_found)
        {
            if (Ab(i, j) != 0) { // pivot not equal to 0
                pivot_found = true;
            } else { // check for a possible swap
                int max_row = i;
                double max_val = 0;
                for (int k = i + 1; k < rows; ++k)
                {
                    double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
                    if (cur_abs > max_val)
                    {
                        max_row = k;
                        max_val = cur_abs;
                    }
                }
                if (max_row != i) {
                    Ab.swapRows(max_row, i);
                    pivot_found = true;
                } else {
                    j++;
                }
            }
        }

        // perform elimination as normal if pivot was found
        if (pivot_found)
        {
            for (int t = i + 1; t < rows; ++t) {
                for (int s = j + 1; s < cols; ++s) {
                    Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
                    if (Ab(t, s) < EPS && Ab(t, s) > -1*EPS)
                        Ab(t, s) = 0;
                }
                Ab(t, j) = 0;
            }
        }

        i++;
        j++;
    }

    return Ab;
}

Matrix Matrix::rowReduceFromGaussian()
{
    Matrix R(*this);
    int rows = R.rows_;
    int cols = R.cols_;

    int i = rows - 1; // row tracker
    int j = cols - 2; // column tracker

    // iterate through every row
    while (i >= 0)
    {
        // find the pivot column
        int k = j - 1;
        while (k >= 0) {
            if (R(i, k) != 0)
                j = k;
            k--;
        }

        // zero out elements above pivots if pivot not 0
        if (R(i, j) != 0) {
            for (int t = i - 1; t >= 0; --t) {
                for (int s = 0; s < cols; ++s) {
                    if (s != j) {
                        R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                        if (R(t, s) < EPS && R(t, s) > -1*EPS)
                            R(t, s) = 0;
                    }
                }
                R(t, j) = 0;
            }

            // divide row by pivot
            for (int k = j + 1; k < cols; ++k) {
                R(i, k) = R(i, k) / R(i, j);
                if (R(i, k) < EPS && R(i, k) > -1*EPS)
                    R(i, k) = 0;
            }
            R(i, j) = 1;
        }
        i--;
        j--;
    }

    return R;
}

Matrix Matrix::inverse() // Нахождение обратной матрицы
{
    if (this->determinant() == 0) {
        throw std::invalid_argument("The inverse matrix cannot be found because the determinant of the matrix is zero");
    }

    Matrix I = Matrix::createIdentity(rows_);
    Matrix AI = Matrix::augment(*this, I);
    Matrix U = AI.gaussianEliminate();
    Matrix IAInverse = U.rowReduceFromGaussian();
    Matrix AInverse(rows_, cols_);
    for (int i = 0; i < AInverse.rows_; ++i) {
        for (int j = 0; j < AInverse.cols_; ++j) {
            AInverse(i, j) = IAInverse(i, j + cols_);
        }
    }
    return AInverse;
}

Matrix Matrix::randomMatrix(int rows, int cols, int min, int max) {
    Matrix A(rows, cols);
    srand(time(0)); // seed the random number generator
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i][j] = min + rand() % (max - min + 1); // generate a random number between min and max
        }
    }
    return A;
}

Matrix Matrix::zeroMatrix(int rows, int cols) {
    Matrix A(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i][j] = 0;
        }
    }
    return A;
}

Matrix Matrix::removeColumns(int index1, int index2) {
    int n = rows_;
    int m = cols_;
    Matrix C(n, m - (index2 - index1 + 1));
    for (int j = 0; j < index1; ++j) {
        for (int i = 0; i < n; ++i) {
            C[i][j] = p[i][j];
        }
    }
    for (int j = index2 + 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            C[i][j - index2 - 1 + index1] = p[i][j];
        }
    }
    return C;
}

// PRIVATE HELPER FUNCTIONS

void Matrix::allocSpace()
{
    p = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        p[i] = new double[cols_];
    }
}

Matrix Matrix::expHelper(const Matrix& m, int num)
{
    if (num < 0) {
        throw std::invalid_argument("The number is negative");
    }

    if (num == 0) { 
        return createIdentity(m.rows_);
    } else if (num == 1) {
        return m;
    } else if (num % 2 == 0) {  // num is even
        return expHelper(m * m, num/2);
    } else {                    // num is odd
        return m * expHelper(m * m, (num-1)/2);
    }
}

// NON-MEMBER FUNCTIONS

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}

Matrix operator/(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp /= m2);
}

Matrix operator/(const Matrix& m, double num)
{
    Matrix temp(m);
    return (temp /= num);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}

void check_broadcastable(const Matrix& m1, const Matrix& m2) {
    std::string error_message = "operands could not be broadcast together with shapes ";
    std::string shape_a = "(" + std::to_string(m1.getRows()) + "," + std::to_string(m1.getCols()) + ")";
    std::string shape_b = "(" + std::to_string(m2.getRows()) + "," + std::to_string(m2.getCols()) + ")";

    throw std::invalid_argument(error_message + shape_a + " " + shape_b);
}