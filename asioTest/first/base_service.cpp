#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::asio;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void client_session(socket_ptr sock) {
	while(true) {
		char data[512];
		boost::system::error_code err;
		size_t len = sock->read_some(buffer(data), err);
		if (err == error::eof) {
			cerr << "err : " <<  err.what() << endl;
			sock->close();
			return;
		}
		if (len > 0) {
			cout << "len"<< len<< data << endl;
			write(*sock, buffer("ok", 2));
		}
	}
}

int main(){
	io_service service;
	ip::tcp::endpoint ep(ip::tcp::v4(), 2001);
	try{
		ip::tcp::acceptor acc(service, ep);
		while(true) {
			socket_ptr sock(new ip::tcp::socket(service));
			acc.accept(*sock);
			boost::thread(boost::bind(client_session, sock));
		}
	}catch(boost::system::system_error ex) {
		cerr << "err : " << ex.code()  << "---"<<  ex.what() << endl;
	}catch(...) {}
	return 0;
}
