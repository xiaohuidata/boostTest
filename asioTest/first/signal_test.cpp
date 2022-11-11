#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;

void signal_handler(const boost::system::error_code& err, int signal) {
	if (err) {
		cerr << "error:" << err.message() << endl;
	} else {
		cout << "signal:" << signal << endl;
	}
	exit(signal);
}

int main(){
	io_service service;
	signal_set sig(service, SIGINT, SIGTERM);
	sig.async_wait(signal_handler);

	service.run();
	return 0;
}
