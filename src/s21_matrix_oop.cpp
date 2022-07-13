#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows < 1 || cols < 1)
        throw std::out_of_range("Error: Wrong matrix size");
    this->matrix_ = nullptr;
    this->createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    this->matrix_ = nullptr;
    this->createMatrix();
    this->copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) : S21Matrix(other) {
    other.removeMatrix();
    other.rows_ = 0;
    other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
    this->removeMatrix();
}


int S21Matrix::getRows() const {
    return this->rows_;
}

void S21Matrix::setRows(const int rows) {
    if (rows < 1)
        throw std::out_of_range("Error: Wrong rows size");
    if (rows != this->rows_)
        this->resizeMatrix(rows, this->cols_);
}

int S21Matrix::getCols() const {
    return this->cols_;
}

void S21Matrix::setCols(const int cols) {
    if (cols < 1)
        throw std::out_of_range("Error: Wrong cols size");
    if (cols != this->cols_)
        this->resizeMatrix(this->rows_, cols);
}


void S21Matrix::createMatrix() {
    this->matrix_ = new double*[this->rows_];
    for (auto row = 0; row < this->rows_; row++)
        this->matrix_[row] = new double[this->cols_]();
}

void S21Matrix::removeMatrix() {
    if (this->matrix_ != nullptr) {
        for (auto row = 0; row < this->rows_; row++) {
            if (this->matrix_[row] != nullptr) {
                delete[] matrix_[row];
                matrix_[row] = nullptr;
            }
        }
        delete[] this->matrix_;
        this->matrix_ = nullptr;
    }
}

void S21Matrix::recreateMatrix(const S21Matrix& other) {
    this->removeMatrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->createMatrix();
}

void S21Matrix::copyMatrix(const S21Matrix& other) {
    for (auto row = 0; row < this->rows_; row++)
        std::memcpy(this->matrix_[row], other.matrix_[row], this->cols_ * sizeof(double));
}

void S21Matrix::resizeMatrix(int rows, int cols) {
    S21Matrix new_matrix(rows, cols);
    int min_rows = (rows < this->rows_) ? rows : this->rows_;
    int min_cols = (cols < this->cols_) ? cols : this->cols_;
    for (auto row = 0; row < min_rows; row++)
        std::memcpy(new_matrix.matrix_[row], this->matrix_[row], min_cols * sizeof(double));
    *this = new_matrix;
}

S21Matrix S21Matrix::getMinorMatrix(int delete_row, int delete_col) {
    S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
    for (auto row = 0, n_row = 0; row < this->rows_; row++) {
        if (row == delete_row)
            continue;
        for (auto col = 0, n_col = 0; col < this->cols_; col++) {
            if (col == delete_col)
                continue;
            minor.matrix_[n_row][n_col] = this->matrix_[row][col];
            n_col++;
        }
        n_row++;
    }
    return minor;
}


bool S21Matrix::isSquare() {
    return (this->rows_ == this->cols_);
}

bool S21Matrix::isEqualSize(const S21Matrix& other) {
    return (this->rows_ == other.rows_ && this->cols_ == other.cols_);
}


bool S21Matrix::operator==(const S21Matrix& other) {
    return this->eq_matrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        if (!this->isEqualSize(other))
            this->recreateMatrix(other);
        this->copyMatrix(other);
    }
    return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
    this->sum_matrix(other);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sum_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
    this->sub_matrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(*this);
    result.sub_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
    this->mul_matrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator*=(const double num) {
    this->mul_number(num);
    return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.mul_number(num);
    return result;
}

double& S21Matrix::operator()(int row, int col) {
    if (row < 0 || col < 0 || row >= this->rows_ || col >= this->cols_)
        throw std::out_of_range("Error: Index out of range");
    return this->matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= this->rows_ || col >= this->cols_)
        throw std::out_of_range("Error: Index out of range");
    return this->matrix_[row][col];
}


bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool result = false;
    if (this == &other) {
        result = true;
    } else if (this->isEqualSize(other)) {
        result = true;
        for (auto row = 0; row < this->rows_ && result; row++) {
            for (auto col = 0; col < this->cols_ && result; col++) {
                if (this->matrix_[row][col] != other.matrix_[row][col]) {
                    result = false;
                }
            }
        }
    }
    return result;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (!this->isEqualSize(other))
        throw std::range_error("Error: Matrices of different size");

    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] += other.matrix_[row][col];
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (!this->isEqualSize(other))
        throw std::range_error("Error: Matrices of different size");

    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] -= other.matrix_[row][col];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            this->matrix_[row][col] *= num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (this->cols_ != other.rows_) {
        throw std::range_error("Error: The columns of the first "
        "matrix is not equal to the rows of the second matrix");
    }

    S21Matrix result(this->rows_, other.cols_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < other.cols_; col++) {
            for (auto col_t = 0; col_t < this->cols_; col_t++) {
                result.matrix_[row][col] += this->matrix_[row][col_t] * other.matrix_[col_t][col];
            }
        }
    }
    *this = result;
}

S21Matrix S21Matrix::transpose() {
    S21Matrix result(this->cols_, this->rows_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            result.matrix_[col][row] = this->matrix_[row][col];
        }
    }
    return result;
}

S21Matrix S21Matrix::calc_complements() {
    if (!this->isSquare())
        throw std::range_error("Matrix is't square");

    S21Matrix result(this->rows_, this->cols_);
    for (auto row = 0; row < this->rows_; row++) {
        for (auto col = 0; col < this->cols_; col++) {
            S21Matrix minor(this->getMinorMatrix(row, col));
            double determ = minor.determinant();
            result.matrix_[row][col] = determ * pow(-1, row + col);
        }
    }
    return result;
}

double S21Matrix::determinant() {
    if (!this->isSquare())
        throw std::range_error("Matrix is't square");

    double result = 0.0;
    if (this->cols_ == 1) {
        result = this->matrix_[0][0];
    } else if (this->cols_ == 2) {
        result = this->matrix_[0][0] * this->matrix_[1][1] -
            this->matrix_[0][1] * this->matrix_[1][0];
    } else {
        for (auto col = 0; col < this->cols_; col++) {
            S21Matrix minor(this->getMinorMatrix(0, col));
            result += pow(-1, col) * this->matrix_[0][col] * minor.determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::inverse_matrix() {
    double determ = this->determinant();
    if (fabs(determ) < 1e-7)
        throw std::range_error("Error: Determinant is 0");

    S21Matrix complements_matrix(this->calc_complements());
    S21Matrix transpose_matrix(complements_matrix.transpose());
    return transpose_matrix * (1. / determ);
}
