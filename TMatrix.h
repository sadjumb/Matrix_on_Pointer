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
		vec = new TVector<T>[size];
		for (size_t i = 0; i < size; ++i)
		{
			vec[i] = TVector<T>(size - i);
		}
	}
	TMatrix(const TMatrix<T>& copy) : size(copy.size)
	{
		vec = new TVector<T>[size];
		for (size_t i = 0; i < size; ++i)
		{
			vec[i] = copy.vec[i];
		}
	}
	~TMatrix()
	{
		delete[] vec;
	}
	TMatrix<T>& operator=(const TMatrix<T>& copy)
	{
		if (this == &copy)
			return *this;
		size = copy.size;
		if (vec != nullptr)
		{
			delete[] vec;
		}

		vec = new TVector<TVector<T>>[size];

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
		{
			tmp.vec[i] = vec[i] + v.vec[i];
		}
		return tmp;
	}
	TMatrix operator-(const TMatrix& v)
	{
		if (size != v.size)
			throw "no equal size";
		TMatrix tmp(*this);
		for (size_t i = 0; i < size; ++i)
		{
			tmp.vec[i] = vec[i] - v.vec[i];
		}
		return tmp;
	}

	TMatrix operator*(const TMatrix& v)
	{
		if (size != v.size)
			throw "no equal size";
		TMatrix tmp(size);
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < vec[i].get_size(); ++j)
				for (size_t k = 0; k < size - j && k < vec[i].get_size(); ++k)
					tmp.vec[i][j] += vec[i][k] * v.vec[k][j];
		return tmp;
	}

	TVector<T>& operator[](int index)
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
	TVector<T>* vec;


	friend std::ostream& operator<<(std::ostream& out, const TMatrix<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			out << r.vec[i] << std::endl;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, const TMatrix<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			in >> r.vec[i];
		}
		return in;
	}

};

