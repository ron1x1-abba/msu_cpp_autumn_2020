#pragma once

#include <iostream>
#include <stdexcept>

class Helper;

class Matrix {
	const size_t rows;
	const size_t columns;
	int* data;
public:
	Matrix(const size_t r, const size_t c);
	Matrix(const Matrix& a);
	~Matrix();
	size_t GetRows() const;
	size_t GetColumns() const;
	Helper operator[](const size_t i);
	Helper operator[](const size_t i) const;
	Matrix& operator*=(const int x);
	Matrix operator+(const Matrix& a) const ;
	bool operator== (const Matrix& a) const;
	bool operator!= (const Matrix& a) const;
	friend std::ostream& operator<<(std::ostream& s,const Matrix& a);
	friend class Helper;
};

class Helper {
	const Matrix& mat;
	size_t rows;
public:
	Helper(Matrix& a, const size_t i);
	Helper(const Matrix& a, const size_t i);
	int& operator[](const size_t j);
	const int& operator[](const size_t j) const;
};
