#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_array.hpp>

using namespace std;
using namespace boost::asio;

io_service  service;
ip::tcp::socket sock(service);

struct shared_buffer{
		boost::shared_array<char> buff;
		int size;
		shared_buffer(size_t size) : buff (new char[size]), size(size) {
		}
		mutable_buffers_1 asio_buff() const {
			return buffer(buff.get(), size);
		}
};

void on_read(shared_buffer buff, const boost::system::error_code& err, std::size_t read_bytes) {
	if (!err) {
		cout << "ptr "  << buff.buff.get() << " bytes " << read_bytes << endl;
	}
	else {
		cerr << "error " << err.what() << "|" << err.message() << endl;
	}
}

void connect_handler(const boost::system::error_code & ec) {
	if (!ec) {
		write(sock, buffer("send ok", 7));
		shared_buffer buff(512);
		sock.async_send(buff.asio_buff(), boost::bind(on_read, buffer, _1, _2));
	} else {
		cerr << "error" << ec.what() << ec.message() <<  endl;
	}
}

int main()
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	sock.async_connect(ep, connect_handler);
	service.run();
	
	return 0;
}
