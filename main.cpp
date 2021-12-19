#include <iostream>
#include "TMatrix.h"
#include <vector>
int main()
{
	TMatrix<int> t1(5);
	for (size_t i = 0; i < 5; ++i)
		for (size_t j = 0; j < 5 - i; ++j)
			t1[i][j] = 1 * j;
	TMatrix<int> t2(t1);
	TVector<int> v(5);
	for (size_t i = 0; i < 5; ++i)
	{
		v[i] = (i + 2) * 3;
	}
	//t1[0] = t1[0] + v;
	std::cout << t1 << t2;
	std::cout << t1 * t2;
	//std::vector<int>* vec = new std::vector<int>[5];
	//std::vector<int> vec2{ 1,2,3,4,5 };
	//vec[0] = vec2;
	//std::cout << vec[0][0];

	return 0;
}