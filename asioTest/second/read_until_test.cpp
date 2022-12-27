#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::tcp::socket sock(service);

typedef buffers_iterator<boost::asio::streambuf::const_buffers_type> uiterator;

pair<uiterator, bool> match_punct(uiterator begin, uiterator end) {
	while (begin != end) {
		if (ispunct(*begin)) {
			return make_pair(begin, true);
		}
		begin++;
	}
	return  make_pair(end, false);
}

boost::asio::streambuf buf;

void on_read(const boost::system::error_code&, size_t)
{
	istream in(&buf);
	string line;
	getline(in, line);
	std::cout << "on_read " << line << std::endl;
	async_read_until(sock, buf, match_punct, on_read);
}

int main()
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
	sock.connect(ep);
	sock.write_some(buffer("login"));
	async_read_until(sock, buf, match_punct, on_read);
	std::cout << "on_read null" << std::endl;
	service.run();
	return 0;
}
