#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost::asio;

boost::mutex mt;
static int cont = 1;
io_service service;

void connect_handler(const boost::system::error_code& e) {
	mt.lock();
	int c = cont++;
	cout << "con" << c << endl;
	if (e) {
		cerr << c << "err:" << e.message() << endl;
	}
	mt.unlock();
}

void timeout_handler(const boost::system::error_code& e) {
	mt.lock();
	int c = cont++;
	cout << "timeout con" << c << endl;
	if (e){
		cerr << c << "err:" << e.message() << endl;
	}
	mt.unlock();
}

void run_service(const int& i) {
	mt.lock();
	cout << "thread " << i << " start" << time(0) <<  endl;
	mt.unlock();
	service.run();
	mt.lock();
	cout << "thread " << i << " end" << time(0) << endl;
	mt.unlock();
}

int main() {
	ip::tcp::socket sock1(service);
	ip::tcp::socket sock2(service);
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	
	sock1.async_connect(ep, connect_handler);
	sock2.async_connect(ep, connect_handler);

	deadline_timer t(service, boost::posix_time::seconds(5));
	t.async_wait(timeout_handler);

	for ( int i = 0; i < 5; ++i) {
		boost::thread(boost::bind(run_service, i));
	}

	int out = 0;
	cin >> out;
	return 0;
}
