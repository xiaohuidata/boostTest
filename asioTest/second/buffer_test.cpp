#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace boost::asio;

struct pod_sample
{
	int i;
	long l;
	char c;
};

void on_read()
{
}

int main()
{
	char b1[512];
	void * b2 = new char[512];
	string b3;
	b3.resize(128);
	pod_sample b4[16];

	vector<pod_sample> b5;
	b5.resize(16);

	boost::array<pod_sample, 16>  b6;
	std::array<pod_sample, 16> b7;

	io_service service;
	ip::tcp::socket sock(service);

	sock.async_send(buffer(b1), on_read);
	sock.async_send(buffer(b2, 512), on_read);
	sock.async_send(buffer(b3), on_read);
	sock.async_send(buffer(b4), on_read);
	sock.async_send(buffer(b5), on_read);
	sock.async_send(buffer(b6), on_read);
	sock.async_send(buffer(b7), on_read);

	return 0;
}
