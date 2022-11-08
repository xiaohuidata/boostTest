#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

io_service service;
ip::tcp::endpoint ep(ip::tcp::v4(), 2001);
ip::tcp::acceptor acc(service, ep);

void start_accept(socket_ptr sock);
void handle_accept(socket_ptr sock, const boost::system::error_code& err) {
	if (err) {
		cerr << "error:" << err.what() << err.message() << endl;
		return;
	}
		char data[512];
		size_t len = sock->read_some(buffer(data));
		if (len > 0) {
			std::string str = data;
			cout << "len"<< len<< str << endl;
			write(*sock, buffer("ok", 2));
		}

	socket_ptr sock_(new ip::tcp::socket(service));
	start_accept(sock_);
}


void start_accept(socket_ptr sock) {
	acc.async_accept(*sock, boost::bind(handle_accept, sock, boost::placeholders::_1));
}

int main(){

	socket_ptr sock(new ip::tcp::socket(service));
	start_accept(sock);
	service.run();

	return 0;
}
