#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
	io_service service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	ip::tcp::socket sock(service);
	sock.connect(ep);
	// TCP套接字可以重用地址
	ip::tcp::socket::reuse_address ra(true);
	sock.set_option(ra);
	std::cout << "reuse_address " << ra.value() << std::endl;
	// 获取套接字读取的数据
	ip::tcp::socket::receive_buffer_size rbss(8192);
	sock.set_option(rbss);
	ip::tcp::socket::receive_buffer_size rbs;
	sock.get_option(rbs);
	std::cout << "receive_buffer_size " <<  rbs.value() << std::endl;
	// 把套接字的缓冲区大小设置为8192
	ip::tcp::socket::send_buffer_size sbs(8192);
	sock.set_option(sbs);
	std::cout << "send_buffer_size " << sbs.value() << std::endl;

	return 0;
}
