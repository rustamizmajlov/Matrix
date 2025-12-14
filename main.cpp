#include <iostream>
#include <vector>
#include <stdexcept>

struct Matrix {
    int rows = 0;
    int cols = 0;
    std::vector<long long> a; // хранение в 1D: a[i*cols + j]

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

Matrix multiply(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        throw std::invalid_argument("Size mismatch");
    }

    Matrix C(A.rows, B.cols);

    // алгоритм: C[i][j] = sum_k A[i][k] * B[k][j]
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Matrix A(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            std::cin >> A(i, j);

    int m2, p;
    std::cin >> m2 >> p;
    Matrix B(m2, p);
    for (int i = 0; i < m2; ++i)
        for (int j = 0; j < p; ++j)
            std::cin >> B(i, j);

    try {
        Matrix C = multiply(A, B);

        for (int i = 0; i < C.rows; ++i) {
            for (int j = 0; j < C.cols; ++j) {
                if (j) std::cout << ' ';
                std::cout << C(i, j);
            }
            std::cout << '\n';
        }
    } catch (...) {
        std::cout << "ERROR\n";
    }

    return 0;
}
