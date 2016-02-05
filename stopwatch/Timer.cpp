
#include <thread>
#include <iostream>
#include <atomic>
#include <unistd.h>
#include "KeyboardController.h"
#include "Timer.h"
#include "TimerView.h"

//ctor
Timer::Timer() {
	std::thread timer(&Timer::run, this);
	ticking_ = false;
	sec_ = 0;
	timer.detach();
}
//start the timer
void Timer::start() {
	ticking_ = true;
}
//stop the timer
void Timer::stop() {
	ticking_ = false;
	//notify();
}
//reset the timer
void Timer::reset() {
	sec_ = 0;
	notify();
}
//returns number of seconds elapsed
unsigned long Timer::get() const {
	return sec_;
}
bool Timer::getTick() const {
	return ticking_;
}
//update timer by command line
void Timer::update(Subject *s) {
	std::string command = ((KeyboardController*) s)->getCommand();
	char cmd_ = command[0];
	switch(cmd_) {
		case 's' :
			std::cout << "\033[0;34m" << "start the timer" << "\033[0;37m" << std::endl;
			start();
			break;
		case 'h' :
			std::cout << "\033[0;31m" << "halt the timer" << "\033[0;37m" << std::endl;
			stop();
			break;
		case 'r' :
			std::cout <<  "\033[0;32m" <<"reset timer to 0" << "\033[0;37m" << std::endl;
    		ticking_ = false;
    		reset();
    		break;
		default :
			;
	}
}
void Timer::run() {
	while(true) {
		if(ticking_ == true) {
			sec_ = sec_ + 1;
			notify();
		}
		sleep(1);
	}
}