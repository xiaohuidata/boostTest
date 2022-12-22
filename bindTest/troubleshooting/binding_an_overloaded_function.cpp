#include <boost/bind.hpp>

struct X
{
	int & get();
	int const& get() const;
};

int main()
{
	boost::bind(&X::get, _1);

	boost::bind(static_cast<int const& (X::*)()const>(&X::get), _1);
	
	int const& (X::*get)() const = &X::get;
	boost::bind(get, _1);
}
