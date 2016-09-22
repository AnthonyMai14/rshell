#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"

#include <unistd.h> //fork, execvp
#include <sys/types.h> //waitpid
#include <sys/wait.h> // waitpid
#include <stdio.h> //perror
#include <stdexcept> //throw
#include <cstring> //c.str()
#include <stdlib.h> //exit
#include <vector>

class Command : public Base{
	private:
		//check to see if keyword "exit" exist
		//if so terminate
		void exitFlag();
		//set index of cmd_line to point to first character in parse_cmd
		//to satisfy requirement for execvp
		void createCharPointer();
		bool callFork();
		
	protected:
		std::vector<std::string> parse_cmd;
		std::vector<char*> cmd_line;
		
	public:
		Command();
		Command(std::vector<std::string> &);
		
		bool execute();

		
};

#endif