#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main() {
	io_service service;
	// 串行口，windows COM7
	//serial_port sp(service, "COM7")
	serial_port sp(service, "/dev/ttys0");

	/*  @sa SettableSerialPortOption @n
	 *  boost::asio::serial_port_base::baud_rate @n
	 *  boost::asio::serial_port_base::flow_control @n
	 *  boost::asio::serial_port_base::parity @n
	 *  boost::asio::serial_port_base::stop_bits @n
	 *  boost::asio::serial_port_base::character_size
	 */
	// 设置端口选项
	serial_port::baud_rate rate(9600);
	sp.set_option(rate);


	char data[512];
	read(sp, buffer(data, 512));

	posix::stream_descriptor sd_in(service, ::dup(STDIN_FILENO));
	read(sd_in, buffer(data, 512));

	return 0;
}
