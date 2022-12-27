// 暂时无法实现
#include <iostream>
#include <boost/asio.hpp>
#include <string>

using namespace std;
using namespace boost::asio;

void on_read(std::streambuf & buf, const boost::system::error_code&, size_t)
{
	istream in(&buf);
	string line;
	getline(in, line);
	cout << " first line:" << line << std::endl;
}

int main()
{
	FILE* file = fopen("async_shared_buffer.cpp", "r");
	if (file == NULL) {
		return -1;
	}

	
	
}
