#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service  service;
ip::tcp::socket sock(service);
void connect_handler(const boost::system::error_code & ec) {
	if (!ec) {
		write(sock, buffer("send ok", 7));
		char data[512];
		size_t len = sock.read_some(buffer(data));

		cout << "len(" << len << ")--" << data << endl;
	} else {
		cout << "error" << ec.what() << ec.message() <<  endl;
	}
}

int main()
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	sock.async_connect(ep, connect_handler);
	service.run();
	
	return 0;
}
