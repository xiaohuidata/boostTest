#include <boost/bind.hpp>

int f(int);

int main()
{
	boost::bind(f, _1);		// OK
	boost::bind(f, _1)();	// error, there is no argument number 1
}
