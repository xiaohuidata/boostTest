#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::udp::endpoint ep(ip::udp::v4(), 2000);
ip::udp::socket sock(service, ep);
ip::udp::endpoint sender_ep(ip::address_v4::from_string("127.0.0.1"), 2002);

int i = 1;
void on_send(const boost::system::error_code& err, std::size_t read_bytes) {
	sleep(5);
	i++;
	cout << "start " << i << endl;
	stringstream ss;
	ss << "ok " << i;
	sock.async_send_to(buffer(ss.str()), sender_ep, on_send );
	cout << "end " << i << endl;
}


int main(int argc, char* argv[])
{
	sock.set_option(ip::udp::socket::broadcast(true));
	cout << "start " << i << endl;
	stringstream ss;
	ss << "ok " << i;
	sock.async_send_to(buffer(ss.str()), sender_ep, on_send );
	cout << "end " << i << endl;
	service.run();
	return 0;
}
