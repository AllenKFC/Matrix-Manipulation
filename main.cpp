#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/**
 * Class to implement a Matrix Multiplication and Transposition of MxN matrices.
 */
class Matrix {
public:

    /**
     * Initialize a Matrix object from a given rows and columns length pair.
     * @param rows Number of rows of the matrix.
     * @param cols Number of colums of the matrix.
     */
    Matrix() {}
    Matrix(int rows, int cols);

    /**
     * Return the number of rows of this matrix.
     * @return Number of rows of this matrix.
     */
    int rows() const { return rows_; }

    /**
     * Return the number of columns of this matrix.
     * @return Number of columns of this matrix.
     */
    int cols() const { return cols_; }

    /**
     * The () operater which takes the indices as input.
     * @param i the row number
     * @param j the column number
     * @return the element at the indices of the matrix
     */
    double& operator()(int i, int j);

    /**
     * Perform a resize method on a matrix into a desired pair of row and column.
     * The additional element in the matrix is zero-filled.
     * @param rows The desired number of rows.
     * @param cols The desired number of columns.
     */
    void resize(int rows, int cols);

    /**
     * Perform a transpose method on a matrix. The Matrix will be transposed 
     * in-place.
     */
    void selfTranspose();
    void print();

    /**
     * Return a new Matrix that is transposed from another matrix.
     * @return a new transposed matrix.
     */
    Matrix transpose() const;

    /**
     * Perform a multiplication on the given matrices.
     * @param a The first matrix of multiplication
     * @return a matrix after multiplication
     */
    Matrix operator*(Matrix& a);

private:
    int rows_ = 0; //A private instance variable which represents the number of rows
    int cols_ = 0; //A private instance variable which represents the number of columns
    vector<vector<double> > data_; //A private instance variable which represents the element in the matrix
};

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), data_(rows, vector<double>(cols)) {
        if (rows < 0 || cols < 0) {
        throw invalid_argument("Matrix dimensions must be non-negative");
    }
}

double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw out_of_range("Matrix index out of range");
    }
    return data_[i][j];
}

void Matrix::resize(int rows, int cols) {
    // Resize the rows first, and then for each row we resize the column size. 
    if (rows < 0 || cols < 0) {
        throw invalid_argument("Matrix dimensions must be non-negative");
    }

    rows_ = rows;
    cols_ = cols;
    data_.resize(rows);
    for (auto& row : data_) {
        row.resize(cols);
    }
}

void Matrix::selfTranspose() {
    // Use two for loops to swap the value of the respective row and column element 
    // for transposition
    for (int i = 0; i < rows_; ++i) {
        for (int j = i+1; j < cols_; ++j) {
            swap(data_[i][j], data_[j][i]);
        }
    }
    swap(rows_, cols_);
}

Matrix Matrix::transpose() const {
    // Use two for loops to fill in the transposed element into a new matrix
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result(j, i) = data_[i][j];
        }
    }
    return result;
}

void Matrix::print() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            cout << data_[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::operator*(Matrix& a) {
    // Get the rows and colums number needed and use two for loops to fill in the 
    // element after multiplication.
    int first_matrix_row = this->rows();
    int first_matrix_col = this->cols();
    int second_matrix_row = a.rows();
    int second_matrix_col = a.cols();

    // throw an exception if the dimensions do not work for multiplication
    if (first_matrix_col != second_matrix_row) {
        throw invalid_argument("Dimensions do not match for multiplication!");
    }

    Matrix result(first_matrix_row, second_matrix_col);
    for (int i = 0; i < first_matrix_row; ++i) {
        for (int j = 0; j < second_matrix_col; ++j) {
            double sum = 0.0;
            for (int k = 0; k < first_matrix_col; ++k) {
                sum += (*this)(i, k) * a(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

int main() {
    return 0;
}
