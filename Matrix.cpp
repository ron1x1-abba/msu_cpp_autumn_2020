#include "Matrix.hpp"

Matrix::Matrix(const size_t r, const size_t c) : rows(r), columns(c) { data = new int[rows * columns]; }

Matrix::Matrix(const Matrix& a) : rows(a.rows), columns(a.columns) {
	data = new int[rows * columns];
	for (size_t i = 0; i < rows * columns; ++i)
		data[i] = a.data[i];
}

Matrix::~Matrix() { delete[] data; }

Helper::Helper(Matrix& a, const size_t i) : mat(a), rows(i) {}

Helper::Helper(const Matrix& a, const size_t i) : mat(a), rows(i) {}

size_t Matrix::GetColumns() const { return columns; }

size_t Matrix::GetRows() const { return rows; }

//I suppose countdown of rows and columns start with 1
Helper Matrix::operator[](const size_t i) { return Helper(*this, i); }

Helper Matrix::operator[](const size_t i) const { return Helper(*this, i);  }

Matrix& Matrix::operator*=(const int x) {
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < columns; ++j)
			data[i * columns + j] *= x;
	return *this;
}

std::ostream& operator<<(std::ostream& s, const Matrix& a) {
	for (size_t i = 0; i < a.rows; ++i){
		for (size_t j = 0; j < a.columns; ++j) {
			s << a.data[i*a.columns + j] << ' ';
		}
		s << '\n';
	}
	return s;
}

Matrix Matrix::operator+(const Matrix& a) const {
	if ((rows == a.rows) && (columns == a.columns)) {
		Matrix m(rows, columns);
		for (size_t i = 1; i <= rows; ++i)
			for (size_t j = 1; j <= columns; ++j)
				m[i][j] = (*this)[i][j] + a[i][j];
		return m;
	}
	else
		throw std::logic_error("Matrices have different size!");
}

bool Matrix::operator==(const Matrix& a) const {
	if ((rows == a.rows) && (columns == a.columns)) {
		for (size_t i = 1; i <= rows; ++i)
			for (size_t j = 1; j <= columns; ++j)
				if ((*this)[i][j] != a[i][j])
					return false;
		return true;
	}
	else
		return false;
}

bool Matrix::operator!=(const Matrix& a) const {
	if ((rows == a.rows) && (columns == a.columns)) {
		for (size_t i = 1; i <= rows; ++i)
			for (size_t j = 1; j <= columns; ++j)
				if ((*this)[i][j] != a[i][j])
					return true;
		return false;
	}
	else
		return true;
}

int& Helper::operator[](const size_t j) {
	if ( ( (rows <= mat.rows) && (rows >= 1) ) && ( (j <= mat.columns) && (j >= 1) ) )
		return mat.data[mat.columns * (rows - 1) + (j - 1)];
	else
		throw std::out_of_range("");
}

const int& Helper::operator[](const size_t j) const {
	if (((rows <= mat.rows) && (rows >= 1)) && ((j <= mat.columns) && (j >= 1)))
		return mat.data[mat.columns * (rows - 1) + (j - 1)];
	else
		throw std::out_of_range("");
}