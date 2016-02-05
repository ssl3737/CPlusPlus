
#ifndef OBSERVER_H
#define OBSERVER_H
 
#include "Subject.h"

class Subject;

class Observer {
public:
	virtual ~Observer() {}
	virtual void update(Subject *) = 0;
protected:
	Observer(){}
};
#endif