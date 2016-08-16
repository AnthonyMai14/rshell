#ifndef COMMAND_H
#define COMMAND_H

#include "terminal.h"

class Command : public Terminal{
	private:
		std::string cmd;
	public:
		//constructor
		Command() : Terminal("cmd") {//default
			cmd = "";
		};
		Command(std::string cmd) : Terminal("cmd") {
			this->cmd = cmd;
		};
		
		//function
		void setCmd(std::string cmd) {
			this->cmd = cmd;
		};
};
#endif
