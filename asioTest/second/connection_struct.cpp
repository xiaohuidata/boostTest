#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

using namespace boost::asio;

io_service service;

struct connection : boost::enable_shared_from_this<connection> {
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<connection> ptr;

	connection() : sock_(service), started_(true) {}

	void start(ip::tcp::endpoint ep) {
		sock_.async_connect(ep, boost::bind(&connection::on_connect, shared_from_this(), _1));
		std::cout << "start" << std::endl;
	}

	void stop() {
		std::cout << "stop" << std::endl;
		if (!started_) return;
		started_ = false;
		sock_.close();
	}

	bool started() { return started_; }

private:
	void on_connect(const error_code& err) {
		// 这里你决定用这个连接做什么：读取或者写入
		if (!err) do_read();
		else stop();
	}

	void on_read(const error_code& err, size_t bytes) {
		if (err) {
			std::cerr << "on_read:error:" << err.what() << std::endl;
			return;
		}
		if (!started()) return;
		std::string msg(read_buffer_, bytes);
		std::cout << "on_read:" << msg << "|" <<  std::endl;
		if (msg.compare(0, 9, "can_login") == 0) do_write("access_data");
		else if (msg.find("data") == 0) process_data(msg);
		else std::cout << "on_read exit" << std::endl;
	}

	void on_write(const error_code& err, size_t bytes) {
		if (err) {
			std::cerr << "on_wirte:error:" << err.what() << bytes << std::endl;
			return;
		}
		do_read();
	}

	void do_read() {
		sock_.async_read_some(buffer(read_buffer_), boost::bind(&connection::on_read, shared_from_this(), _1, _2));
	}

	void do_write(const std::string & msg) {
		std::cout << "do_write start:" << write_buffer_ << std::endl;
		if ( !started() ) return;
		// 注意：因为在做另外一个async_read操作之前你想要发送多个消息，
		// 所以你需要多个写入buffer
		std::copy(msg.begin(), msg.end(), write_buffer_);
		std::cout << "do_write:" << write_buffer_ << std::endl;
		sock_.async_write_some(buffer(write_buffer_, msg.size()), boost::bind(&connection::on_write, shared_from_this(), _1, _2));
	}

	void process_data(const std::string & msg) {
		// 处理服务端来的内容，然后启动另外一个写入操作
		std::cout << "process_data:" << msg << std::endl;
	}

private:
	ip::tcp::socket sock_;
	enum { max_msg = 1024 };
	char read_buffer_[max_msg];
	char write_buffer_[max_msg];
	bool started_;
};

int main() {
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 2001);
	connection::ptr(new connection)->start(ep);

	service.run();
	return 0;
}

