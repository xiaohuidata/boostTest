#include <boost/config.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <iostream>
#include <typeinfo>

using namespace boost;

struct visitor
{
    template<class T> void operator()( reference_wrapper<T> const & r ) const
    {
        std::cout << "Reference to " << typeid(T).name() << " @ " << &r.get() << " (with value " << r.get() << ")" << std::endl;
    }

    template<class T> void operator()( T const & t ) const
    {
        std::cout << "Value of type " << typeid(T).name() << " (with value " << t << ")" << std::endl;
    }
};

int f(int & i, int & j, int)
{
    ++i;
    --j;
    return i + j;
}

int main()
{
    int x = 2;
    int y = 7;
    visitor v;
    visit_each(v, bind<int>(bind(f, ref(x), _1, 42), ref(y)), 0);
}
