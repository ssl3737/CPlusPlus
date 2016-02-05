
#ifndef TIMER_H
#define TIMER_H

#include <atomic>
#include <unistd.h>
#include "Observer.h"
#include "Subject.h"

class Timer: public Subject, public Observer {
public:
	//ctor
	Timer();
	//start the timer
	void start();
	//stop the timer
	void stop();
	//reset the timer
	void reset();
	//returns number of seconds elapsed
	unsigned long get() const;
	bool getTick() const;
	// (*)
	Timer(const Timer&) = delete;
	// (*)	
	Timer& operator=(const Timer&) = delete;
	//update timer by command line
	void update(Subject *s);
private:
	//The number of seconds elapsed
	std::atomic<long> sec_;
	//is timer ticking or not?
	std::atomic<bool> ticking_;
	//is timer ticking or not?
	void run();
};
#endif