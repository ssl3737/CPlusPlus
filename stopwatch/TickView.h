
#ifndef TICKVIEW
#define TICKVIEW
 
#include <iostream>
#include "TimerView.h"
#include "TickView.h"

class TickView: public TimerView {
public:
	TickView(Timer *timer, std::ostream& os = std::cout) : TimerView(timer, os) {}
	//Display tick * 
	void display(std::ostream& os) const override {
		if (timer_->getTick()) {
			os << "TickView  " << "*" << "  ";
		}
	}
};
#endif