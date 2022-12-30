#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <string>

using namespace boost::asio;

#define MEM_FN(x)      boost::bind(&self_type::x,shared_from_this())
#define MEM_FN1(x,y)   boost::bind(&self_type::x,shared_from_this(),y)
#define MEM_FN2(x,y,z) boost::bind(&self_type::x,shared_from_this(),y,z)

io_service service;

class talk_to_svr : public boost::enable_shared_from_this<talk_to_svr>, boost::noncopyable {
	typedef talk_to_svr self_type;
	talk_to_svr(const std::string& message) : sock_(service), started_(true), message_(message) {}
	void start(ip::tcp::endpoint ep) {
		sock_.async_connect(ep, MEM_FN1(on_connect, _1));
		std::cout << "start" << std::endl;
	}


public:
	typedef boost::system::error_code error_code;
	typedef boost::shared_ptr<talk_to_svr> ptr;

	static ptr start(ip::tcp::endpoint ep, const std::string & message) {
		ptr  new_(new talk_to_svr(message));
		new_->start(ep);
		return new_;
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
		if (!err) do_write(message_ + "\n");
		else stop();
	}

	void on_read(const error_code& err, size_t bytes) {
		if (err) {
			std::cerr << "on_read:error:" << err.what() << std::endl;
			stop();
			return;
		}
		std::string copy(read_buffer_, bytes - 1);
		std::cout << "service echoed our " << message_ << ": " << (copy == message_ ? "OK" : "FAIL") << std::endl;
	}

	void on_write(const error_code& err, size_t bytes) {
		if (err) {
			std::cerr << "on_wirte:error:" << err.what() << bytes << std::endl;
			return;
		}
		do_read();
	}

	void do_read() {
		async_read(sock_, buffer(read_buffer_), MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
	}

	void do_write(const std::string & msg) {
		std::cout << "do_write start:" << write_buffer_ << std::endl;
		if ( !started() ) return;
		// 注意：因为在做另外一个async_read操作之前你想要发送多个消息，
		// 所以你需要多个写入buffer
		std::copy(msg.begin(), msg.end(), write_buffer_);
		std::cout << "do_write:" << write_buffer_ << std::endl;
		sock_.async_write_some(buffer(write_buffer_, msg.size()), MEM_FN2(on_write, _1, _2));
	}

	size_t read_complete(const error_code& err, size_t bytes) {
		if (err) return 0;
		bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
		return found? 0: 1;
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
	std::string message_;
};

int main() {
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
	char* messages[] = { "John says hi", "so does James", "Lucy got home", 0};
	for (char ** message = messages; *message; ++message) {
		talk_to_svr::start(ep, *message);
	}

	service.run();
	return 0;
}

