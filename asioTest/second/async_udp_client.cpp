#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::udp::socket sock(service);
ip::udp::endpoint sender_ep;
char buff[512];

void on_read(const boost::system::error_code& err, std::size_t read_bytes) {
	std::cout << "read " << read_bytes << std::endl;
	sock.async_receive_from(buffer(buff), sender_ep, on_read);
	std::cout << "read buff " << buff << std::endl;
}

int main()
{
	ip::udp::endpoint ep(ip::address::from_string("127.0.0.1"), 2002);
	sock.open(ep.protocol());
	sock.set_option(ip::udp::socket::reuse_address(true));
	sock.bind(ep);
	sock.async_receive_from(buffer(buff, 512), sender_ep, on_read);
	std::cout << "read1" << buff << std::endl;
	service.run();

}
