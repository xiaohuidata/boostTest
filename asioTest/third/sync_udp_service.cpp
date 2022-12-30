#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;

typedef boost::system::error_code error_code;

io_service service;

void handle_connections() {
	char buff[1024];
	ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 8001));
	while (true) {
		ip::udp::endpoint sender_ep;
		int bytes = sock.receive_from(buffer(buff), sender_ep);
		std::cout << "receive:" << buff << std::endl;
		std::string msg(buff, bytes);
		sock.send_to(buffer(msg), sender_ep);
	}
}

int main() {
	handle_connections();
}
