#include <iostream>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>
#include <algorithm>

struct X
{
	void f()
	{
		std::cout << "X::x:" << ++x << std::endl;
	}

	int x = 0;
};

void g(std::vector<X> &v)
{
	std::for_each(v.begin(), v.end(), boost::mem_fn(&X::f));
}

void h(std::vector<X *> const & v)
{
	std::for_each(v.begin(), v.end(), boost::mem_fn(&X::f));
}

void k(std::vector<boost::shared_ptr<X> > const & v)
{
	std::for_each(v.begin(), v.end(), boost::mem_fn(&X::f));
}

int main()
{
	std::vector<X> vecx = { X{}, X{}, X{}};
	g(vecx);
	g(vecx);

	std::cout << std::endl;
	std::vector<X*> vecxx = { new X(), new X(), new X() };
	h(vecxx);
	h(vecxx);
	std::cout << std::endl;

	std::vector<boost::shared_ptr<X> > vexpx = { boost::shared_ptr<X>(new X), boost::shared_ptr<X>(new X), boost::shared_ptr<X>(new X)};
	k(vexpx);
	k(vexpx);
	return 0;
}
