#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

io_service service;

void func(int i) {
	std::cout << " func called, i = " << i << std::endl;
}

void run_dispatch_and_post() {
	for (int i = 0; i < 10; i +=2) {
		service.dispatch(boost::bind(func, i));
		service.post(boost::bind(func, i+1));
	}
}

int main()
{
	service.post(run_dispatch_and_post);
	service.run();
	return 0;
}
