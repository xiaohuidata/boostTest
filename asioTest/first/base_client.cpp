#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
	io_service  service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	ip::tcp::socket sock(service);

	bool connect = false;
	try{
		sock.connect(ep);
		connect = true;
	} catch(boost::system::system_error e) {
		cerr << "error:" << e.code() << endl;
	}
	boost::system::error_code err;

	if (!connect) {
		sock.connect(ep, err);
	}

	if (err) {
		cerr << "error:" << err.what() << endl;
		return 0;
	}
	write(sock, buffer("send ok", 7));

	char data[512];
	size_t len = sock.read_some(buffer(data));

	cout << "len(" << len << ")--" << data << endl;
	
	return 0;
}
