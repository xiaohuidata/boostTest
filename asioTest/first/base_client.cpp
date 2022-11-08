#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
	io_service  service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	ip::tcp::socket sock(service);
	sock.connect(ep);

	write(sock, buffer("send ok", 7));

	char data[512];
	size_t len = sock.read_some(buffer(data));

	cout << "len(" << len << ")--" << data << endl;
	
	return 0;
}
