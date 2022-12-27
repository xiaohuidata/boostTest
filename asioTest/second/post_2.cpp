#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;
io_service service;
boost::mutex _mutex;
void func(int i) {
	_mutex.lock();
	std::cout << "func called, i = " << i << "/" << std::this_thread::get_id() << std::endl;
	_mutex.unlock();
}

void worker_thread() {
	service.run();
}

int main()
{
	io_service::strand strand_one(service), strand_two(service);
	for (int i = 0 ; i < 5; ++i) {
		service.post(strand_one.wrap(boost::bind(func, i)));
	}
	for (int i = 5 ; i < 10; ++i) {
		service.post(strand_two.wrap(boost::bind(func, i)));
	}
	boost::thread_group threads;
	for (int i = 0; i < 3; ++i) {
		threads.create_thread(worker_thread);
	}
	// 等待所有线程被创建完
	boost::this_thread::sleep(boost::posix_time::millisec(500));
	threads.join_all();
}
