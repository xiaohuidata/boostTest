#include <iostream>
#include <boost/bind.hpp>

using namespace std;

struct X
{
	bool f(int a) {
		return a;
	}
};

int main()
{
	X x;
	shared_ptr<X> p(new X);
	int i = 5;

	cout << bind(&X::f, boost::ref(x), _1)(i) << endl; 	// x.f(i)
	cout << bind(&X::f, &x, _1)(i) << endl;			// (&x)->f(i)
	cout << bind(&X::f, x, _1)(i) << endl;			// (internal copy of x).f(i)
	cout << bind(&X::f, p, _1)(i) << endl;			// (internal copy of p)->f(i)
}
