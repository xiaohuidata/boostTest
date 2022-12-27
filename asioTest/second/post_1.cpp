#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;
io_service service;
void func(int i) {
	std::cout << "func called, i = " << i << std::this_thread::get_id() << std::endl;
}

void worker_thread() {
	std::cout << "worker_thread " << std::this_thread::get_id() << std::endl;
	service.run();
}

int main()
{
	for (int i = 0 ; i < 10; ++i) {
		service.post(boost::bind(func, i));
	}
	boost::thread_group threads;
	for (int i = 0; i < 3; ++i) {
		threads.create_thread(worker_thread);
	}
	// 等待所有线程被创建完
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	threads.join_all();
}
