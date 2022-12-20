#include <boost/config.hpp>

#include <boost/bind.hpp>
#include <iostream>
#include <string>

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

template<class F> void test(F f)
{
    // f as bind(f, _1 ...)("x", "y")
    cout << f("x", "y") << "\n";
}

int main()
{
    // compose_f_gx
    test(bind(f, bind(g, _1)));

    // compose_f_hxy
    test(bind(f, bind(h, _1, _2)));

    // compose_h_fx_gx
    test(bind(h, bind(f, _1), bind(g, _1)));

    // compose_h_fx_gy
    test(bind(h, bind(f, _1), bind(g, _2)));

    // compose_f_k
    test(bind(f, bind(k)));
    return 0;
}
