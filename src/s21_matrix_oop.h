#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <stdexcept>
#include <cmath>
#include <cstring>

class S21Matrix {
 private:
    int rows_, cols_;
    double **matrix_;

    void createMatrix();
    void removeMatrix();
    void recreateMatrix(const S21Matrix& other);
    void copyMatrix(const S21Matrix& other);
    void resizeMatrix(int rows, int cols);
    S21Matrix getMinorMatrix(int delete_row, int delete_col);

    bool isSquare();
    bool isEqualSize(const S21Matrix& other);

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int getRows() const;
    void setRows(const int rows);
    int getCols() const;
    void setCols(const int cols);

    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix operator+=(const S21Matrix& other);
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-=(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*=(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*=(const double num);
    S21Matrix operator*(const double num);
    double& operator()(int row, int col);
    double& operator()(int row, int col) const;

    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();
};

#endif  //  SRC_S21_MATRIX_OOP_H_
