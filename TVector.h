#pragma once
#include <iostream>

template<class T>
class TVector
{
public:
	TVector() : size(0), start(0), pArr(nullptr){}
	TVector(size_t _size, size_t _start = 0) : size(_size), start(_start), pArr(new T[size]{}) {}
	TVector(const TVector<T>& copy) : size(copy.size), start(copy.start), pArr(new T[size])
	{
		for(size_t i = 0; i < size; ++i)
		{
			pArr[i] = copy.pArr[i];
		}
	}
	//TVector(const TVector<T>&& copy) : size(std::swap(size, copy.size)), start(std::swap(start, copy.start)), pArr(std::swap(pArr, copy.pArr)){}
	~TVector()
	{
		delete[] pArr;
		pArr = nullptr;
	}

	T& operator[](size_t index) const
	{
		if (index - start < 0 || start < 0 || start < 0)
			throw std::out_of_range("start is negative");

		return pArr[index - start];
	}
	T& operator[](size_t index)
	{
		if (index - start < 0 || index - start > size - 1 || start < 0)
			throw std::out_of_range("start is negative");
		return pArr[index - start];
	}


	TVector<T>& operator=(const TVector<T>& r)
	{
		if (this == &r)
			return *this;
		size = r.size;
		start = r.start;
		if(pArr != nullptr)
			delete[] pArr;
		pArr = new T[size]{};

		for (size_t i = 0; i < size; ++i)
		{
			pArr[i] = r.pArr[i];
		}
		return *this;
	}	
	TVector<T>& operator=(TVector<T>&& r)
	{
		if (this == &r)
			return *this;
		std::swap(size, r.size);
		std::swap(start, r.start);
		std::swap(pArr, r.pArr);
		
		return *this;
	}

	bool operator==(const TVector& v) const
	{
		if (this == &v)
			return true;
		if (size != v.size)
			return false;
		for (size_t i = 0; i < size; i++)
			if (pArr[i] != v.pArr[i])
				return false;
		return true;
	}
	bool operator!=(const TVector& v) const
	{
		return !(*this == v);
	}

	TVector operator+(const T& val)
	{
		TVector<T> tmp(*this);
		for (int i = 0; i < size; i++)
		{
			tmp.pArr[i] += val;
		}
		return tmp;
	}
	TVector operator-(const T& val)
	{
		TVector<T> tmp(*this);
		for (int i = 0; i < size; i++)
		{
			tmp.pArr[i] -= val;
		}
		return tmp;
	}
	TVector operator*(const T& val)
	{
		TVector<T> tmp(*this);
		for (int i = 0; i < size; i++)
		{
			tmp.pArr[i] *= val;
		}
		return tmp;
	}
	
	TVector operator+(const TVector& v)
	{
		if (size != v.size || start != v.start)
			throw "no equal size";
		TVector<T> tmp(*this);
		for (int i = 0; i < size; i++)
		{
			tmp.pArr[i] += v.pArr[i];
		}
		return tmp;
	}
	TVector operator-(const TVector& v)
	{
		if (size != v.size || start != v.start)
			throw "no equal size";
		TVector<T> tmp(*this);
		for (int i = 0; i < size; i++)
		{
			tmp.pArr[i] -= v.pArr[i];
		}
		return tmp;
	}
	T operator*(const TVector& v)
	{
		if (size != v.size || start != v.start)
			throw "no equal size";
		T res = 0;
		for (int i = 0; i < size; i++)
		{
			res += pArr[i] * v.pArr[i];
		}
		return res;
	}
	size_t get_size() const
	{
		return size;
	}


	
private:
	size_t size;
	size_t start;
	T* pArr;
private:
	friend std::ostream& operator<<(std::ostream& out, const TVector<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			out << r.pArr[i] << " ";
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, const TVector<T>& r)
	{
		for (size_t i = 0; i < r.size; ++i)
		{
			in >> r[i];
		}
		return in;
	}
};



