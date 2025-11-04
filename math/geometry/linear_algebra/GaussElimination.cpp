//
// Created by Arpan Pathak on 01/11/25.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Type alias for clarity
using Matrix = std::vector<std::vector<double>>;

/**
 * @brief Pretty Prints the augmented matrix M with minimal formatting.
 * * Uses standard insertion (<<) without manipulators like setw or setprecision.
 * * @param M The augmented matrix (n x (n+1)).
 */
#include <cstdio> // Required for printf (or just use <iostream> on some compilers)
#include <vector>

using Matrix = std::vector<std::vector<double>>;

/**
 * @brief Prints the augmented matrix M using C-style printf for fixed-width spacing.
 * * Uses a fixed width of 10 characters with 4 decimal places.
 */
void printMatrix(const Matrix& M) {
    if (M.empty()) return;
    int n_cols = M[0].size();

    for (const auto& row : M) {
        for (int j = 0; j < n_cols; ++j) {
            // "%10.4f" means: print a floating-point number, use 10 characters total width, and show 4 decimal places.
            std::printf("%10.4f", row[j]);

            // Add the separator for the augmented part
            if (j == n_cols - 2) {
                std::printf(" |");
            }
        }
        std::printf("\n"); // Newline
    }
}

/**
 * @brief Prints the solution vector x with minimal formatting.
 */
void printVector(const std::vector<double>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << "x[" << i << "] = " << v[i] << "\n";
    }
}

/**
 * @brief Performs forward elimination with row normalization, WITHOUT Partial Pivoting.
 * * WARNING: This implementation is unstable.
 * * @param M The augmented matrix (modified in place).
 * @return true if elimination succeeded, false on division by zero.
 */
bool forwardElimination(Matrix& M) {
    int n = M.size();
    if (n == 0) return false;

    const double EPSILON = 1e-12;

    for (int i = 0; i < n; ++i) {

        double pivot_value = M[i][i];

        // Critical Check: Fail if pivot is zero
        if (std::abs(pivot_value) < EPSILON) {
            std::cerr << "CRITICAL ERROR: Pivot is zero. Cannot proceed." << std::endl;
            return false;
        }

        // 1. Normalization: Make the pivot M[i][i] equal to 1
        for (int j = i; j < n + 1; ++j) {
            M[i][j] /= pivot_value;
        }

        // 2. Elimination: Make all elements below the pivot zero
        for (int k = i + 1; k < n; ++k) {

            double factor = M[k][i];

            // Apply the operation: Row_k = Row_k - factor * Row_i
            for (int j = i; j < n + 1; ++j) {
                M[k][j] -= factor * M[i][j];
            }
        }
    }

    return true;
}

/**
 * @brief Performs back substitution to find the solution vector x.
 */
std::vector<double> backSubstitution(const Matrix& M) {
    int n = M.size();
    if (n == 0) return {};

    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += M[i][j] * x[j];
        }
        // Solved as M[i][i] is 1
        x[i] = M[i][n] - sum;
    }
    return x;
}

/**
 * @brief Solves a system of linear equations A*x = b using Gaussian elimination.
 */
std::vector<double> solve(const Matrix& A, const std::vector<double>& b) {
    int n = A.size();

    // Create the Augmented Matrix (A|b)
    Matrix M = A;
    for (int i = 0; i < n; ++i) {
        M[i].push_back(b[i]);
    }

    if (!forwardElimination(M)) {
        return {};
    }

    return backSubstitution(M);
}

// --- Main Method with Sample ---

int main() {
    // Example System:
    // x + 2y + 3z = 10
    // 2x + 6y + 102z = 4
    // 4x - 8y + 4z = 8

    Matrix A = {
        {1.0, 2.0, 3.0},
        {2.0, 6.0, 102.0},
        {4.0, -8.0, 4.0}
    };
    std::vector<double> b = {10.0, 4.0, 8.0};

    std::cout << "Solving System of Equations (A*x = b):\n";
    std::cout << "--------------------------------------\n";

    // Display Initial Augmented Matrix
    std::cout << "Initial Augmented Matrix:\n";
    Matrix initial_M = A;
    for (int i = 0; i < A.size(); ++i) initial_M[i].push_back(b[i]);
    printMatrix(initial_M);
    std::cout << "\n";

    // Solve the system
    std::vector<double> x = solve(A, b);

    // Display Results
    if (!x.empty()) {
        std::cout << "Solution Vector x:\n";
        printVector(x);
    } else {
        std::cout << "Failed to find a unique solution.\n";
    }

    return 0;
}
