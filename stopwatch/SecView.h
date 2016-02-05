
#ifndef SECVIEW_H
#define SECVIEW_H
 
#include "TimerView.h"
#include <iostream>

class SecView: public TimerView {
	public:
		SecView(Timer *timer, std::ostream& os = std::cout): TimerView(timer, os) {}
		virtual void display(std::ostream& os) const override {
			os << "SecView: " << timer_->get() << "  ";
		}
};
#endif