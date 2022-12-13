#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <time.h>

using namespace std;
using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

io_service service;
ip::tcp::endpoint ep(ip::tcp::v4(), 2001);
ip::tcp::acceptor acc(service, ep);

bool r = false;

void start_accept(socket_ptr sock);
void handle_accept(socket_ptr sock, const boost::system::error_code& err) {
	if (err) {
		cerr << "error:" << err.what() << err.message() << endl;
		return;
	}

	r = true;
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
//	acc.async_accept(*sock, boost::bind(handle_accept, sock, boost::placeholders::_1));
	acc.async_accept(*sock, boost::bind(handle_accept, sock, _1));
}

void deadline_handler(const boost::system::error_code& ) {
	cout << (r ? "read successfully" : "read failed") << endl;
	cout << "exit" << time(0) << endl;
	exit(0);
}


int main(){

	socket_ptr sock(new ip::tcp::socket(service));
	start_accept(sock);

	deadline_timer t(service, boost::posix_time::milliseconds(1000));
	cout << "start:" << time(0) << endl;
	//t.wait();
	cout <<  "end:" << time(0) << endl;
	t.async_wait( &deadline_handler);
	service.run();
	return 0;
}
