#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <algorithm>

using namespace std;
using namespace boost;

class X
{
public:
	static bool visible(const string & str) {
		if (str == "Xu") {
			return true;
		}
		return false;
	}

	static string name(const string& str){
		return str;
	}
};

int main()
{
	vector<string> vec {"Later", "Paul", "Perter", "Xu"};

	auto first  = vec.begin();
	auto last = vec.end();

	remove_if(first, last, !bind(&X::visible, _1));
	cout << vec.size() << endl;
	vec.resize(vec.size()-1);
	for (auto it : vec) {
		cout << it << ", ";
	}
	cout << "  first " << *first << " size " <<vec.size() <<  endl;

	auto iter = find_if(first, last, bind(&X::name, _1) == "Perter");
	cout << *iter << endl;
	iter = find_if(first, last, bind(&X::name, _1) == "Perter" || bind(&X::name, _1) == "Paul");
	cout << *iter << endl;

	cout << endl;
	cout << (bind(&X::name, _1) == _2)("Perter", "Paul") << endl;

	cout << endl;

	sort(first, last, bind(&X::name, _1) > bind(&X::name, _2));
	cout << vec.size() <<  " >> " << endl;
	for (auto it : vec) {
		cout << it << ", ";
	}
	cout << endl;


	return 0;
}
