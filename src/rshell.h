#ifndef RSHELL_H
#define RSHELL_H

#include "command.h"
//#include "connector.h"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> //getlogin, get username
#include <stdlib.h> //exit()

class RShell {
    protected:
		std::string input;
		std::vector<Command*> v;
    public:
		RShell(){
		    input = "";	
		};
		
		void run();
	// void parse(std::string user_input, std::vector<Command*> &v) {
	// 	for (int i = 0; i < user_input; ++i) {
	// 	}	
	// };
};

void RShell::run() {
    bool user_continue = true;
    
    while (user_continue) {
		std::cout << '$';
		std::string user_input = "";
		getline(std::cin, user_input);
		
		//if exit, terminate program
		if (user_input == "exit" || user_input == "EXIT") {
			exit(EXIT_SUCCESS);
		}
		
		//take out comments
		for (unsigned i = 0; i < user_input.size(); ++i) {
		    if (user_input.at(i) == '#') {
				user_input = user_input.substr(0, i);
		    }
		}

		//iterate through user_input & parse through it
    }
};
#endif
