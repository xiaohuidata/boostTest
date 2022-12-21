#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

io_service  service;
ip::tcp::socket sock(service);

void on_read(char *ptr, const boost::system::error_code& err, std::size_t read_bytes) {
	if (!err) {
		cout << "ptr " << ptr << " bytes " << read_bytes << endl;
		delete[] ptr;
		ptr = NULL;
	}
	else {
		if (ptr) {
			delete[] ptr;
			ptr = NULL;
		}
	}
}

void connect_handler(const boost::system::error_code & ec) {
	if (!ec) {
		write(sock, buffer("send ok", 7));
		char * buff = new char[512];
		sock.async_send(buffer(buff, 512), boost::bind(on_read, buff, _1, _2));

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
