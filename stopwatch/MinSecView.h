
#ifndef MINSECVIEW_H
#define MINSECVIEW_H

#include <iostream>
#include "TimerView.h"

class MinSecView: public TimerView{
public:
	MinSecView(Timer *timer, std::ostream& os = std::cout): TimerView(timer, os) {}
		//Display minutes and seconds 
	void display(std::ostream& os) const override {
		int min = timer_->get() / 60;
		int sec = timer_->get() % 60;
		os << "MinSecView  " << min << ": " << sec  << std::endl;
	}
};
#endif