#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::tcp::socket sock(service);
char buff[512];
int offset = 0;

size_t up_to_enter(const boost::system::error_code &, size_t bytes)
{
	for (size_t i = 0; i < bytes; ++i) {
		if (buff[i + offset] == '\n')
		  return 0;
	}
	return 1;
}

void on_read(const boost::system::error_code&, size_t)
{
	cout << "on_read " << buff << endl;
	async_read(sock, buffer(buff), up_to_enter, on_read);
}

int main()
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	sock.connect(ep);
	sock.write_some(buffer("login"));
	async_read(sock, buffer(buff), up_to_enter, on_read);
	cout << "on_read null" << buff << endl;
	service.run();
	return 0;
}
