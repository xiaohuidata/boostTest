#include <boost/config.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/bind/apply.hpp>

using namespace std;
using namespace boost;

string f(const string& x)
{
    return "f(" + x + ")";
}

string g(const string& x)
{
    return "g(" + x + ")";
}

string h(const string& x, const string& y)
{
    return "h(" + x + "," + y + ")";
}

string k()
{
    return "k()";
}

int main()
{
    cout << bind(f, bind(g, _1))("x") << endl; // f(g(x))

    typedef void (*pf)(int);
    std::vector<pf> v;
//    std::for_each(v.begin(), v.end(), bind(_1, 5));
    std::for_each(v.begin(), v.end(), bind(boost::apply<void>(), _1, 5));


    return 0;
}
