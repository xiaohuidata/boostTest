#include <boost/bind.hpp>

struct X
{
	int f(int);
};

int f(int, int);

int main()
{
	boost::bind(f, 1);		// error, f takes two arguments
	boost::bind(f, 1, 2);	// OK

	boost::bind(&X::f, 1);		// error, X::f takes two arguments
	boost::bind(&X::f, _1, 1);	// OK
}
