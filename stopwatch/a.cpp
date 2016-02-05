#include <thread>
#include <iostream>
#include "KeyboardController.h"
#include "MinSecView.h"
#include "TickView.h"
#include "SecView.h"
#include "Timer.h"
 
using namespace std;

int main() {
	//Create a timer
	Timer *timer = new Timer();
	//Display tick *
	TickView tick(timer);
	//Display seconds view
	SecView sec(timer);
	//Display minutes and seconds view
	MinSecView minSec(timer);
	//Create a keyboard controller
	KeyboardController control;
	
	control.subscribe(timer);
	control.start();
	return 0;
}