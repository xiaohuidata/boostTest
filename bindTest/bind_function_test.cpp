#include <iostream>
#include <boost/bind.hpp>

using namespace std;
int f (int a, int b)
{
	return a + b;
}
int g(int a, int b, int c)
{
	return a + b + c;
}

int main()
{
	auto func = bind(f, _2, _1);
	cout << func (4, 3) << endl;
	cout << bind(f, _2, _1)(3, 4) << endl;

	cout << bind(g, _1, 9, _1) (2) << endl;
	cout << bind(g, _3, _3, _3) (1, 2, 3) << endl;
	cout << bind(g, _1, _1, _1) (1, 2, 3) << endl;

	int i = 5;
	cout << bind(f, i, _1)(3) << endl;

	cout << bind(f, ref(i), _1)(4) << endl;
	cout << bind(f, cref(i), _1)(5) << endl;
	return 0;
}
