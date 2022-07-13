#include "s21_matrix_oop.h"
#include <gtest/gtest.h>

class S21MatrixTest : public testing::Test {
 protected:
    S21Matrix *matrix_3x3;
    S21Matrix *matrix_4x3;
    S21Matrix *matrix_temp;

    void SetUp() {
        matrix_3x3 = new S21Matrix();
        matrix_3x3->operator()(0, 0) = 0;
        matrix_3x3->operator()(0, 1) = 1;
        matrix_3x3->operator()(0, 2) = 2;
        matrix_3x3->operator()(1, 0) = 3;
        matrix_3x3->operator()(1, 1) = 4;
        matrix_3x3->operator()(1, 2) = 5;
        matrix_3x3->operator()(2, 0) = 6;
        matrix_3x3->operator()(2, 1) = 7;
        matrix_3x3->operator()(2, 2) = 8;

        matrix_4x3 = new S21Matrix(4, 3);
        matrix_4x3->operator()(0, 0) = 0;
        matrix_4x3->operator()(0, 1) = 1;
        matrix_4x3->operator()(0, 2) = 2;
        matrix_4x3->operator()(1, 0) = 3;
        matrix_4x3->operator()(1, 1) = 4;
        matrix_4x3->operator()(1, 2) = 5;
        matrix_4x3->operator()(2, 0) = 6;
        matrix_4x3->operator()(2, 1) = 7;
        matrix_4x3->operator()(2, 2) = 8;
        matrix_4x3->operator()(3, 0) = 9;
        matrix_4x3->operator()(3, 1) = 10;
        matrix_4x3->operator()(3, 2) = 11;
    }

    void TearDown() {
        delete matrix_3x3;
        delete matrix_4x3;
    }
};

TEST_F(S21MatrixTest, constructor) {
    S21Matrix matrix;
    EXPECT_EQ(3, matrix.getRows());
    EXPECT_EQ(3, matrix.getCols());
}

TEST_F(S21MatrixTest, constructorWithParameters) {
    S21Matrix matrix(5, 6);
    EXPECT_EQ(5, matrix.getRows());
    EXPECT_EQ(6, matrix.getCols());
}

TEST_F(S21MatrixTest, constructorWithParametersError) {
    EXPECT_THROW(matrix_temp = new S21Matrix(0, 0), std::out_of_range);
}

TEST_F(S21MatrixTest, constructorCopy) {
    S21Matrix matrix(*matrix_4x3);
    EXPECT_EQ(4, matrix.getRows());
    EXPECT_EQ(3, matrix.getCols());
    EXPECT_EQ(4, matrix_4x3->getRows());
    EXPECT_EQ(3, matrix_4x3->getCols());
    EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, constructorMove) {
    S21Matrix matrix_copy(*matrix_4x3);
    S21Matrix matrix(std::move(*matrix_4x3));
    EXPECT_EQ(4, matrix.getRows());
    EXPECT_EQ(3, matrix.getCols());
    EXPECT_EQ(1, matrix_copy == matrix);
    EXPECT_EQ(0, matrix_4x3->getRows());
    EXPECT_EQ(0, matrix_4x3->getCols());
}

TEST_F(S21MatrixTest, getColsAndRows) {
    EXPECT_EQ(3, matrix_3x3->getRows());
    EXPECT_EQ(3, matrix_3x3->getCols());
    EXPECT_EQ(4, matrix_4x3->getRows());
    EXPECT_EQ(3, matrix_4x3->getCols());
}

TEST_F(S21MatrixTest, setColsAndRows) {
    matrix_3x3->setRows(4);
    EXPECT_EQ(4, matrix_3x3->getRows());
    EXPECT_THROW(matrix_3x3->setRows(-1), std::out_of_range);
    matrix_3x3->setCols(4);
    EXPECT_EQ(4, matrix_3x3->getCols());
    EXPECT_THROW(matrix_3x3->setCols(0), std::out_of_range);
}

TEST_F(S21MatrixTest, qualityOperator) {
    S21Matrix matrix, empty_matrix;
    EXPECT_EQ(0, *matrix_3x3 == *matrix_4x3);
    EXPECT_EQ(0, *matrix_3x3 == matrix);
    EXPECT_EQ(1, empty_matrix == matrix);
    EXPECT_EQ(1, *matrix_3x3  == *matrix_3x3);
}

TEST_F(S21MatrixTest, equalsOperator) {
    S21Matrix matrix;
    matrix = *matrix_3x3;
    EXPECT_EQ(1, *matrix_3x3 == matrix);
    matrix = *matrix_4x3;
    EXPECT_EQ(1, *matrix_4x3 == matrix);
}

TEST_F(S21MatrixTest, plusAndEqualsOperator) {
    S21Matrix result;
    result(0, 0) = 0;
    result(0, 1) = 2;
    result(0, 2) = 4;
    result(1, 0) = 6;
    result(1, 1) = 8;
    result(1, 2) = 10;
    result(2, 0) = 12;
    result(2, 1) = 14;
    result(2, 2) = 16;
    S21Matrix test_result;
    test_result = *matrix_3x3 + *matrix_3x3;
    *matrix_3x3 += *matrix_3x3;
    EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, plusAndEqualsOperatorError) {
    EXPECT_THROW(*matrix_3x3 + *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, minusAndEqualsOperator) {
    S21Matrix result, test_result, matrix;
    matrix(0, 0) = 0;
    matrix(0, 1) = 1;
    matrix(0, 2) = 2;
    matrix(1, 0) = 3;
    matrix(1, 1) = 4;
    matrix(1, 2) = 5;
    matrix(2, 0) = 6;
    matrix(2, 1) = 7;
    matrix(2, 2) = 8;
    test_result = *matrix_3x3 - *matrix_3x3;
    *matrix_3x3 -= matrix;
    EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, minusAndEqualsOperatorError) {
    EXPECT_THROW(*matrix_3x3 - *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, mulMatrixAndEqualsOperator) {
    S21Matrix result;
    result(0, 0) = 15;
    result(0, 1) = 18;
    result(0, 2) = 21;
    result(1, 0) = 42;
    result(1, 1) = 54;
    result(1, 2) = 66;
    result(2, 0) = 69;
    result(2, 1) = 90;
    result(2, 2) = 111;
    S21Matrix test_result;
    test_result = *matrix_3x3 * *matrix_3x3;
    *matrix_3x3 *= *matrix_3x3;
    EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, mulMatrixAndEqualsOperatorError) {
    EXPECT_THROW(*matrix_3x3 * *matrix_4x3, std::range_error);
}

TEST_F(S21MatrixTest, mulNumberAndEqualsOperator) {
    S21Matrix result;
    result(0, 0) = 0;
    result(0, 1) = 5;
    result(0, 2) = 10;
    result(1, 0) = 15;
    result(1, 1) = 20;
    result(1, 2) = 25;
    result(2, 0) = 30;
    result(2, 1) = 35;
    result(2, 2) = 40;
    S21Matrix test_result;
    test_result = *matrix_3x3 * 5;
    *matrix_3x3 *= 5;
    EXPECT_EQ(1, result == *matrix_3x3 && result == test_result);
}

TEST_F(S21MatrixTest, bracketsOperator) {
    EXPECT_EQ(0, matrix_3x3->operator()(0, 0));
    EXPECT_EQ(1, matrix_3x3->operator()(0, 1));
    EXPECT_EQ(2, matrix_3x3->operator()(0, 2));
    EXPECT_EQ(3, matrix_3x3->operator()(1, 0));
    EXPECT_EQ(4, matrix_3x3->operator()(1, 1));
    EXPECT_EQ(5, matrix_3x3->operator()(1, 2));
    EXPECT_EQ(6, matrix_3x3->operator()(2, 0));
    EXPECT_EQ(7, matrix_3x3->operator()(2, 1));
    EXPECT_EQ(8, matrix_3x3->operator()(2, 2));
}

TEST_F(S21MatrixTest, bracketsOperatorError) {
    EXPECT_THROW(matrix_3x3->operator()(-1, 0), std::out_of_range);
    EXPECT_THROW(matrix_3x3->operator()(1, 4), std::out_of_range);
}

TEST_F(S21MatrixTest, bracketsOperatorConst) {
    S21Matrix const matrix;
    EXPECT_EQ(0, matrix.operator()(2, 2));
}

TEST_F(S21MatrixTest, bracketsOperatorConstError) {
    S21Matrix const matrix;
    EXPECT_THROW(matrix.operator()(-1, 0), std::out_of_range);
    EXPECT_THROW(matrix.operator()(1, 4), std::out_of_range);
}

TEST_F(S21MatrixTest, transpose) {
    S21Matrix result(3, 4);
    result(0, 0) = 0;
    result(0, 1) = 3;
    result(0, 2) = 6;
    result(0, 3) = 9;
    result(1, 0) = 1;
    result(1, 1) = 4;
    result(1, 2) = 7;
    result(1, 3) = 10;
    result(2, 0) = 2;
    result(2, 1) = 5;
    result(2, 2) = 8;
    result(2, 3) = 11;
    S21Matrix test_result;
    test_result = matrix_4x3->transpose();
    EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, complements) {
    matrix_3x3->operator()(0, 0) = -5;
    S21Matrix result;
    result(0, 0) = -3;
    result(0, 1) = 6;
    result(0, 2) = -3;
    result(1, 0) = 6;
    result(1, 1) = -52;
    result(1, 2) = 41;
    result(2, 0) = -3;
    result(2, 1) = 31;
    result(2, 2) = -23;
    S21Matrix test_result;
    test_result = matrix_3x3->calc_complements();
    EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, complementsError) {
    EXPECT_THROW(matrix_4x3->calc_complements(), std::range_error);
}

TEST_F(S21MatrixTest, determinant) {
    EXPECT_EQ(0, matrix_3x3->determinant());
    matrix_3x3->operator()(0, 0) = -5;
    EXPECT_EQ(15, matrix_3x3->determinant());
    S21Matrix matrix_1x1(1, 1);
    matrix_1x1(0, 0) = 5;
    EXPECT_EQ(5, matrix_1x1.determinant());
}

TEST_F(S21MatrixTest, determinantError) {
    EXPECT_THROW(matrix_4x3->determinant(), std::range_error);
}

TEST_F(S21MatrixTest, inverse) {
    matrix_3x3->operator()(0, 0) = 2;
    matrix_3x3->operator()(0, 1) = 5;
    matrix_3x3->operator()(0, 2) = 7;
    matrix_3x3->operator()(1, 0) = 6;
    matrix_3x3->operator()(1, 1) = 3;
    matrix_3x3->operator()(1, 2) = 4;
    matrix_3x3->operator()(2, 0) = 5;
    matrix_3x3->operator()(2, 1) = -2;
    matrix_3x3->operator()(2, 2) = -3;
    S21Matrix result;
    result(0, 0) = 1;
    result(0, 1) = -1;
    result(0, 2) = 1;
    result(1, 0) = -38;
    result(1, 1) = 41;
    result(1, 2) = -34;
    result(2, 0) = 27;
    result(2, 1) = -29;
    result(2, 2) = 24;
    S21Matrix test_result;
    test_result = matrix_3x3->inverse_matrix();
    EXPECT_EQ(1, result == test_result);
}

TEST_F(S21MatrixTest, inverseError) {
    EXPECT_THROW(matrix_3x3->inverse_matrix(), std::range_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
