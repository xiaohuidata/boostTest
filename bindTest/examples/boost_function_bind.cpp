#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

class button
{
public:
	boost::function<void()> onClick;
};

class player
{
public:
	void play()
	{
		cout << "play" << endl;
	}
	void stop()
	{
		cout << "stop" << endl;
	}
};

button playButton, stopButton;
player thePlayer;

void connect()
{
	playButton.onClick = boost::bind(&player::play, &thePlayer);
	stopButton.onClick = boost::bind(&player::stop, &thePlayer);
}

int main() {
	connect();

	cout << "start" << endl;
	playButton.onClick();
	stopButton.onClick();
}
