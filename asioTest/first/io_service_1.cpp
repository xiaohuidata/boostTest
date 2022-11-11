#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

static int cont = 1;

void connect_handler(const boost::system::error_code& e) {
	int c = cont++;
	cout << "con" << c << endl;
	if (e) {
		cerr << c << "err:" << e.message() << endl;
	}
}

void timeout_handler(const boost::system::error_code& e) {
	int c = cont++;
	cout << "timeout con" << c << endl;
	if (e){
		cerr << c << "err:" << e.message() << endl;
	}
}

int main() {
	io_service service;
	ip::tcp::socket sock1(service);
	ip::tcp::socket sock2(service);
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	
	sock1.async_connect(ep, connect_handler);
	sock2.async_connect(ep, connect_handler);

	deadline_timer t(service, boost::posix_time::seconds(5));
	t.async_wait(timeout_handler);
	service.run();
}
