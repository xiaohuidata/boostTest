#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main() {
		io_service service;
		ip::udp::socket sock(service);
		sock.open(ip::udp::v4());
		ip::udp::endpoint receiver_ep(ip::address::from_string("127.0.0.1"), 2002);
		sock.send_to(buffer("testing"), receiver_ep);
		char buff[1024];
		ip::udp::endpoint sender_ep;
		sock.receive_from(buffer(buff), sender_ep);
		cout << "receive " << buff << endl;
		sock.close();
		return 0;
}
