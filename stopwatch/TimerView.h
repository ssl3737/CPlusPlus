
#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <string>
#include <iostream>
#include "Observer.h"
#include "Timer.h"

class TimerView: public Observer {
public:
	explicit TimerView(Timer *timer, std::ostream& os = std::cout) : timer_(timer), out_(&os) {
		timer_->subscribe(this);
	}
	virtual void update(Subject *) {
		display(*out_);
	}
		// display 
	virtual void display(std::ostream& os) const = 0;
protected:
	Timer *timer_;
	std::ostream *out_;
};
#endif