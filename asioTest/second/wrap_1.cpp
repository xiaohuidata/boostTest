#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;
using namespace std;

io_service service;
void dispatched_func_1() {
	cout << "dispatched 1" << endl;
}

void dispatched_func_2() {
	cout << "dispatched 2" << endl;
}

void test(boost::function<void()> func) {
	cout << "test" << endl;
	service.dispatch(dispatched_func_1);
	func();
}

void service_run() {
	service.run();
}

int main()
{
	test(service.wrap(dispatched_func_2));
	boost::thread th(service_run);
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	th.join();
	return 0;
}
