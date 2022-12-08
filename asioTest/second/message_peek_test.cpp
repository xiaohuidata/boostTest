#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main() {
		io_service service;
		//ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
		ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
		ip::tcp::socket sock(service);
		sock.open(ip::tcp::v4());
		sock.connect(ep);
		sock.write_some(buffer("GET /index.html\r\n"));
		char buff[1024];
		sock.receive(buffer(buff), ip::tcp::socket::message_peek);
		cout << "read1 " << buff << endl;
		memset(buff, 0, 1024);
		sock.receive(buffer(buff));
		cout << "read2 " << buff << endl;
		sock.shutdown(ip::tcp::socket::shutdown_receive);
		sock.close();
		return 0;
}
