#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
	// ip address
	ip::address addr = ip::address::from_string("127.0.0.1");
	cout << addr << endl;

	// core 
	// ip::address addrwww = ip::address::from_string("www.yahoo.com");
	
	//endpoint
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
	ip::tcp::endpoint ep1;
	ip::tcp::endpoint ep2(ip::tcp::v4(), 80);

	io_service service;
	ip::tcp::resolver resolver(service);
	ip::tcp::resolver::query query("www.baidu.com", "80");

//	ip::tcp::resolver::iterator iter = resolver.resolve(query);
	for (auto iter : resolver.resolve(query)) {
		ip::tcp::endpoint epr = iter;
		cout << epr.address().to_string() << " -- :" << epr.port() << endl;
		//cout << epr.address().to_string() << ":" << epr.port() << "/" << epr.protocol() << endl;
	}

	ip::tcp::resolver::results_type qus = resolver.resolve(query);
	for (auto it = qus.begin(); it != qus.end(); it++) {
		ip::tcp::endpoint epr = *it;
		cout << epr.address().to_string() << " -- :" << epr.port() << endl;
	}

	return 0;
}

