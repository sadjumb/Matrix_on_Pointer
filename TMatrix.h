#pragma once
#include "TVector.h"
#include <string>

template <class T>
class TMatrix
{
public:
	TMatrix() : size(0), vec(nullptr) {}
	TMatrix(size_t _size)
	{
		size = _size;
		vec = new T* [size];
		for (size_t i = 0; i < size; ++i)
		{
			vec[i] = new T[size - i]{ T() };
		}
	}
	TMatrix(const TMatrix<T>& copy) : size(copy.size)
	{
		vec = new T*[size];
		for (size_t i = 0; i < size; ++i)
		{
			vec[i] = new T[size - i]{ T() };
		}
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size - i; ++j)
			{
				vec[i][j] = copy.vec[i][j];
			}
		}
	}
	~TMatrix()
	{
		for (size_t i = 0; i < size; ++i)
		{
			delete[] vec[i];
		}
		delete[] vec;
	}
	TMatrix<T>& operator=(const TMatrix<T>& copy)
	{
		if (this == &copy)
			return *this;
		size = copy.size;
		if (vec != nullptr)
		{
			for (size_t i = 0; i < size; ++i)
				delete[] vec[i];
			delete[] vec;
		}

		vec = new T * [size];
		for (size_t i = 0; i < size; ++i)
		{
			vec[i] = new T[size - i]{ T() };
		}

		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size - i; ++j)
			{
				vec[i][j] = copy.vec[i][j];
			}
		}

		return *this;
	}

	TMatrix operator+(const TMatrix& v)
	{
		if (size != v.size)
			throw "no equal size";
		TMatrix tmp(*this);
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size - i; ++j)
				tmp.vec[i][j] += v.vec[i][j];
		
		return tmp;
	}
	TMatrix operator-(const TMatrix& v)
	{
		if (size != v.size)
			throw "no equal size";
		TMatrix tmp(*this);
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size - i; ++j)
				tmp.vec[i][j] -= v.vec[i][j];
		return tmp;
	}

	TMatrix operator*(const TMatrix& v)
	{
		if (size != v.size)
			throw "no equal size";
		TMatrix tmp(size);
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size - i; ++j)
				for (size_t k = 0; k < size - j && k < size - i; ++k)
					tmp.vec[i][j] += vec[i][k] * v.vec[k][j];
		return tmp;
	}

	T*& operator[](int index)
	{
		if (index < 0 || index > size - 1)
			throw std::out_of_range("start is negative");
		return vec[index];
	}
	TVector<T>& operator[](int index) const
	{
		if (index < 0 || index > size - 1)
			throw std::out_of_range("start is negative");
		return vec[index];
	}
	size_t get_size() const
	{
		return size;
	}
	std::string ToString() const
	{
		std::string str;
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size - i; ++j)
			{
				str.append(std::to_string(vec[i][j]));
				str += ' ';
			}
			str += '\n';
		}
		return str;
	}

private:
	size_t size;
	T** vec;


	friend std::ostream& operator<<(std::ostream& out, const TMatrix<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			for (size_t j = 0; j < r.size - i; ++j)
			{
				out << r.vec[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, const TMatrix<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			for (size_t j = 0; j < r.size - i; ++j)
			{
				in >> r.vec[i][j];
			}
		}
		return in;
	}

};

