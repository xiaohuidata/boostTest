#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::udp::endpoint ep(ip::udp::v4(), 2002);
ip::udp::socket sock(service, ep);

int main(int argc, char* argv[])
{
	ip::udp::endpoint sender_ep;
	char buff[1024];
	int bytes = sock.receive_from(buffer(buff), sender_ep);
	cout << "in " << bytes << "<<" << buff << ">>" << endl;
	sock.send_to(buffer("ok"), sender_ep);

	return 0;
}
