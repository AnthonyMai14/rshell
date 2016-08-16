#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
	private:
		std::string cmd;
	public:
		Command() : cmd("") {};
		void setCmd(std::string cmd) {
			this->cmd = cmd;
		}
};
#endif
