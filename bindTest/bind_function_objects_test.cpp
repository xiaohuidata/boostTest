#include <iostream>
#include <cassert>
#include <boost/bind.hpp>
#include <algorithm>

using namespace std;

struct F
{
	int operator() (int a, int b) {return a - b;}
	bool operator() (long a, long b) {return a == b;}
};

struct F2
{
	int s;
	typedef void result_type;
	void operator()(int x) { s += x; }
};

int main()
{
	F f;
	int x = 104;
	cout << bind<int>(f, _1, _1)(x) << endl;                 // f(x, x), i.e, zero
	cout << bind<int>(f, _1, _2)(x, 100) << endl;            // f(x, x), i.e, zero

	F2 f2 = {0};
	int a[] = { 1, 2, 3 };
	std::for_each(a, a+3, bind(ref(f2), _1));

	assert(f2.s == 6);

	return 0;
}
