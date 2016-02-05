
#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <list>
#include "Observer.h"

class Subject{
public:
	virtual ~Subject() {}
		// subscribe an observer
	virtual void subscribe(Observer *obs) {
		observers_.push_back(obs);
	}
		// unsubscribe an observer
	virtual void unsubscribe(Observer *obs) {
		observers_.remove(obs);
	}
		// ask each subscribed observer to update itself
	virtual void notify() {
		for (auto x : observers_) {
			x->update(this);
		}
	}
protected:
	Subject() {}
private:
	//The list of observers
	std::list<Observer *> observers_;
};
#endif