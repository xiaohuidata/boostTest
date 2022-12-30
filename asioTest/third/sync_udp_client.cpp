#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;
typedef boost::system::error_code error_code;

io_service service;
ip::udp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

void sync_echo(std::string msg) {
	ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
	sock.send_to(buffer(msg), ep);
	char buf[1024];
	ip::udp::endpoint sender_ep;
	int bytes = sock.receive_from(buffer(buf), sender_ep);
	std::string copy(buf, bytes);
	std::cout << "server echoed our " << msg << ": " << (copy == msg ? "OK" : "FAIL") << std::endl;
	sock.close();
}

int main()
{
	char* messages[] = { "John says hi", "so does James", "Lucy just got home", "Boost.Asio is Fun!", 0};
	boost::thread_group threads;
	for (char ** message = messages; *message; ++message) {
		threads.create_thread(boost::bind(sync_echo, *message));
		boost::this_thread::sleep(boost::posix_time::millisec(100));
	}
	threads.join_all();
	return 0;
}
