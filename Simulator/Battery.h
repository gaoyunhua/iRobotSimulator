#ifndef __BATTERY__H_
#define __BATTERY__H_

struct Battery
{
	int capacity;
	int consume_rate;
	int recharge_rate;
	int level;

//public:
	//Battery();
	Battery(int _capacity, int _consume_rate, int _recharge_rate) :capacity(_capacity), consume_rate(_consume_rate)
		, recharge_rate(_recharge_rate), level(_capacity){}

};

#endif