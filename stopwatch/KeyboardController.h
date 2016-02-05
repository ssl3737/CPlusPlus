
#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H
 
#include "Subject.h"
#include <iostream>
#include <string>

class KeyboardController: public Subject {
public:
	KeyboardController() {}
	~KeyboardController() {}
		//start the loop to get user commands
	virtual void start();
		// return the command
	virtual std::string getCommand() const;
private:
	std::string cmd_;
};
inline std::string KeyboardController::getCommand() const {
	return cmd_;
}
inline void KeyboardController::start() {
	char command;
	std::string cmdLine;
	std::string prompt = "Enter a command that begins with the character, s for start, h for halt or r for reset!";
	
	std::cout << prompt << std::endl;
	while(getline(std::cin, cmdLine)) {
		command = cmdLine[0];
		switch(command) {
			case 's' :
				cmd_ = "s";
    			notify();
    			break;
			case 'r' :
				cmd_ = "r";
    			notify();
    			break;
			case 'h' :
				cmd_ = "h";
	    		notify();
	    		break;
			default :
				std::cout << prompt << std::endl;
    	}
    	continue;
    }
}
#endif