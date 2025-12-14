#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

struct Matrix {
    int rows = 0;
    int cols = 0;
    std::vector<long long> a; // a[i*cols + j]

    Matrix() = default;

    Matrix(int r, int c) : rows(r), cols(c), a(static_cast<size_t>(r) * c, 0) {
        if (r < 0 || c < 0) throw std::invalid_argument("Negative matrix size");
    }

    long long& operator()(int r, int c) {
        return a[static_cast<size_t>(r) * cols + c];
    }

    long long operator()(int r, int c) const {
        return a[static_cast<size_t>(r) * cols + c];
    }
};

Matrix add(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        throw std::invalid_argument("Size mismatch for addition");
    }

    Matrix C(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            C(i, j) = A(i, j) + B(i, j);
    return C;
}

// (опционально) чтобы можно было писать C = A + B;
Matrix operator+(const Matrix& A, const Matrix& B) {
    return add(A, B);
} // Идея перегрузки оператора для сложения матриц — стандартная практика. [web:75]

Matrix multiply(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        throw std::invalid_argument("Size mismatch for multiplication");
    }

    Matrix C(A.rows, B.cols);

    for (int i = 0; i < A.rows; ++i) {
        for (int k = 0; k < A.cols; ++k) {
            long long aik = A(i, k);
            for (int j = 0; j < B.cols; ++j) {
                C(i, j) += aik * B(k, j);
            }
        }
    }
    return C;
}

static Matrix readMatrix() {
    int r, c;
    std::cin >> r >> c;
    Matrix M(r, c);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            std::cin >> M(i, j);
    return M;
}

static void printMatrix(const Matrix& M) {
    for (int i = 0; i < M.rows; ++i) {
        for (int j = 0; j < M.cols; ++j) {
            if (j) std::cout << ' ';
            std::cout << M(i, j);
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string op;
    std::cin >> op; // "mul" или "add"

    try {
        Matrix A = readMatrix();
        Matrix B = readMatrix();

        if (op == "mul") {
            Matrix C = multiply(A, B);
            printMatrix(C);
        } else if (op == "add") {
            Matrix C = add(A, B); // или: Matrix C = A + B;
            printMatrix(C);
        } else {
            std::cout << "ERROR\n";
        }
    } catch (...) {
        std::cout << "ERROR\n";
    }

    return 0;
}
