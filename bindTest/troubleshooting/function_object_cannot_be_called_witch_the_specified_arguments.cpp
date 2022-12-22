#include <boost/bind.hpp>

int f(int);

int main()
{
	boost::bind(f, "incompatible");			// OK so far, no call
	boost::bind(f, "incompatible")();		// error, "incompatible" is not an int
	boost::bind(f, _1);						// OK
	boost::bind(f, _1)("incompatible");		// error, "incompatible" is not an int
}
