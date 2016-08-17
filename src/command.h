#ifndef COMMAND_H
#define COMMAND_H

#include "terminal.h"

#include <iostream> //cout
#include <unistd.h> //fork, execvp, waitpid
#include <stdexcept> //throw
#include <cstring> //c.str()
#include <stdlib.h> //exit

class Command : public Terminal{
	private:
		char* cmd_exec;
		char* cmd_argu;
		
		int status; //cmd execute successful(1), unsuccessful(-1)
		
		void execute(char **arr);
		
	public:
		//constructor
		Command() : Terminal("cmd") {
			status = 0;
		};
		//destructor
		~Command() {
			delete [] cmd_exec;
			delete [] cmd_argu;
		}

		//function
		void setCmd(std::string cmd);
		void setArg(std::string argu);
		void execute(); //override virtual
		
		int getStatus();
		
};

void Command::setCmd(std::string cmd) {
	this->cmd_exec = new char[cmd.size() + 1];
	strcpy(cmd_exec, cmd.c_str());
	this->cmd_exec[cmd.size()] = '\0';
	
};
void Command::setArg(std::string argu) {
	this->cmd_argu = new char[argu.length()];
	strcpy(cmd_argu, argu.c_str());
	this->cmd_argu[argu.size()] = '\0';
}

void Command::execute(char **arr) {
	int pid = fork();
	
	if (pid < 0) {//if child error
		//fork error
		exit(1);
	}
	else if (pid == 0) { //if child
		if (execvp(*arr, arr) < 0 ) {
			status = -1;
			exit(1);
		}
		status = 1;
	}
	else{ //if parent
		
	}
};

void Command::execute() {
	
	char *arr[] = {cmd_exec, cmd_argu, NULL};
	execute(arr);
};

int Command::getStatus() {
	return status;
};
#endif
