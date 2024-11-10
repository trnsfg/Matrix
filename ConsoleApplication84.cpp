#include <iostream>
#include <ctime>

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** data;

    void allocateMemory() {
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    void freeMemory() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        allocateMemory();
    }

    ~Matrix() {
        freeMemory();
    }

    void input() {
        std::cout << "Enter matrix elements (" << rows << "x" << cols << "):" << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cin >> data[i][j];
            }
        }
    }

    void fillRandom(T minValue = 0, T maxValue = 100) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = minValue + rand() % (maxValue - minValue + 1);
            }
        }
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const T& value) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] / value;
            }
        }
        return result;
    }

    T maxElement() const {
        T max = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] > max) {
                    max = data[i][j];
                }
            }
        }
        return max;
    }

    T minElement() const {
        T min = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] < min) {
                    min = data[i][j];
                }
            }
        }
        return min;
    }
};

int main() {
    srand(time(0));

    Matrix<int> matrix1(2, 2);
    Matrix<int> matrix2(2, 2);

    matrix1.fillRandom(1, 10);
    matrix2.fillRandom(1, 10);

    std::cout << "Matrix 1:" << std::endl;
    matrix1.display();

    std::cout << "Matrix 2:" << std::endl;
    matrix2.display();

    Matrix<int> sum = matrix1 + matrix2;
    std::cout << "Sum of matrices:" << std::endl;
    sum.display();

    Matrix<int> difference = matrix1 - matrix2;
    std::cout << "Difference of matrices:" << std::endl;
    difference.display();

    Matrix<int> product = matrix1 * matrix2;
    std::cout << "Product of matrices:" << std::endl;
    product.display();

    int scalar = 2;
    Matrix<int> division = matrix1 / scalar;
    std::cout << "Matrix 1 divided by " << scalar << ":" << std::endl;
    division.display();

    std::cout << "Max element in Matrix 1: " << matrix1.maxElement() << std::endl;
    std::cout << "Min element in Matrix 1: " << matrix1.minElement() << std::endl;

    return 0;
}
