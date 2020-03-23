#ifndef MATRIX_CPP
#define MATRIX_CPP


#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) {
	mat.resize(_rows);
	for (unsigned i = 0; i < mat.size(); i++) {
		mat[i].resize(_cols, _initial);
	}
	rows = _rows;
	cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
	mat = other.mat;
	rows = other.get_rows();
	cols = other.get_cols();
}

// (Virtual) Destructor                                                                                                                                                       
template<typename T>
Matrix<T>::~Matrix() {}

// Assignment Operator                                                                                                                                                        
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	if (&other == this)
		return *this;

	unsigned new_rows = other.get_rows();
	unsigned new_cols = other.get_cols();

	mat.resize(new_rows);
	for (unsigned i = 0; i < mat.size(); i++) {
		mat[i].resize(new_cols);
	}

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			mat[i][j] = other(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;

	return *this;
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] + other(i, j);
		}
	}

	return result;
}

// Cumulative addition of this matrix and another                                                                                                                             
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
	unsigned rows = other.get_rows();
	unsigned cols = other.get_cols();

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			this->mat[i][j] += other(i, j);
		}
	}

	return *this;
}

// Subtraction of this matrix and another                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
	unsigned rows = other.get_rows();
	unsigned cols = other.get_cols();
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] - other(i, j);
		}
	}

	return result;
}

// Cumulative subtraction of this matrix and another                                                                                                                          
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
	unsigned rows = other.get_rows();
	unsigned cols = other.get_cols();

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			this->mat[i][j] -= other(i, j);
		}
	}

	return *this;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
	unsigned rows = other.get_rows();
	unsigned cols = other.get_cols();
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			for (unsigned k = 0; k < rows; k++) {
				result(i, j) += this->mat[i][k] * other(k, j);
			}
		}
	}

	return result;
}

// Cumulative left multiplication of this matrix and another                                                                                                                  
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
	Matrix result = (*this) * other;
	(*this) = result;
	return *this;
}



// Matrix/scalar addition                                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator+(const T& other) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] + other;
		}
	}

	return result;
}

// Matrix/scalar subtraction                                                                                                                                                  
template<typename T>
Matrix<T> Matrix<T>::operator-(const T& other) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] - other;
		}
	}

	return result;
}

// Matrix/scalar multiplication                                                                                                                                               
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& other) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] * other;
		}
	}

	return result;
}

// Matrix/scalar division                                                                                                                                                     
template<typename T>
Matrix<T> Matrix<T>::operator/(const T& other) {
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result(i, j) = this->mat[i][j] / other;
		}
	}

	return result;
}

// Multiply a matrix with a vector                                                                                                                                            
template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& other) {
	std::vector<T> result(other.size(), 0.0);

	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result[i] = this->mat[i][j] * other[j];
		}
	}

	return result;
}

// Obtain a vector of the diagonal elements                                                                                                                                   
template<typename T>
std::vector<T> Matrix<T>::diag_vec() {
	std::vector<T> result(rows, 0.0);

	for (unsigned i = 0; i < rows; i++) {
		result[i] = this->mat[i][i];
	}

	return result;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
	return this->mat[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
	return this->mat[row][col];
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned Matrix<T>::get_rows() const {
	return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned Matrix<T>::get_cols() const {
	return this->cols;
}

#endif