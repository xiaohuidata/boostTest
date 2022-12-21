#include <iostream>
#include <boost/bind.hpp>
#include <vector>
#include <algorithm>

using namespace std;
using namespace boost;

class image {
public:
	int im = 333;
};

class animation
{
public:
	void advance(int ms) {
		advanced += ms;
	}
	bool inactive() const {
		return inactived;
	}
	void render(image& targe) const {
		cout << targe.im << ":" << advanced << endl;
	}

	
public:
	bool inactived = false;
	int advanced = 0;
};

vector<animation> anims;

template<class C, class P> void erase_if(C& c, P pred)
{
	c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}

void update(int ms)
{
	std::for_each(anims.begin(), anims.end(), boost::bind(&animation::advance, _1, ms));
	erase_if(anims, boost::mem_fn(&animation::inactive));
}

void render(image& target)
{
	std::for_each(anims.begin(), anims.end(), boost::bind(&animation::render, _1, boost::ref(target)));
}


int main()
{
	animation anim;
	anim.advanced = 1;
	anims.push_back(anim);
	anim.advanced = 2;
	anims.push_back(anim);
	anim.advanced = 3;
	anims.push_back(anim);
	anim.advanced = 4;
	anims.push_back(anim);
	anim.advanced = 5;
	anim.inactived = true;
	anims.push_back(anim);
	anim.advanced = 6;
	anims.push_back(anim);

	image targe;
	targe.im = 1;
	render(targe);

	cout << endl;

	update(2);
	targe.im = 2;
	render(targe);
}
