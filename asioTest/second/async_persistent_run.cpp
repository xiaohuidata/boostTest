#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::tcp::socket sock(service);
char buff_read[1024], buff_write[1024] = "ok";

void on_read(const boost::system::error_code &, std::size_t);
void on_write(const boost::system::error_code &, std::size_t)
{
	sock.async_read_some(buffer(buff_read), on_read);
}

void on_read(const boost::system::error_code &, std::size_t)
{
	cout << "on_read " << buff_read << endl;
	sock.async_write_some(buffer(buff_write, 3), on_write);
}

void on_connect(const boost::system::error_code &)
{
	//sock.async_read_some(buffer(buff_read), on_read);
	sock.async_write_some(buffer(buff_write, 3), on_write);
}

int main()
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	sock.async_connect(ep, on_connect);
	service.run();
	return 0;
}
