#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

class MyPrint
{
public:
    void operator()(int v)
    {
        cout << v << " ";
    }
};
class MyPrints: public binary_function<int, int, void>
{
public:
    void operator()(int a, int b) const
    {
        cout << "a:" << a;
        cout << " b:" << b << endl;
    }
};

int main()
{
    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;

    int addNum = 100;
    for_each(v.begin(), v.end(), bind1st(MyPrints(), addNum));

    // 第一个大于10的数
    auto it = find_if(v.begin(), v.end(), bind1st(less<int>(), 10));
    cout << *it << endl;

    // 第一个大于10的数
    auto it1 = find_if(v.begin(), v.end(), bind2nd(greater<int>(), 10));
    cout << *it1 << endl;
	return 0;
}
