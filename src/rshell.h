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
		std::vector<Terminal*> v;
    public:
		RShell(){
		    input = "";	
		};
		
		void run();
		void parse(std::string user_input);
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
		parse(user_input);
		//go through vector and check connectors 
		//Note: use size to see if connector exist or not
    }
};

void RShell::parse(std::string user_input) {
	
	for (unsigned i = 0; i < user_input.size(); ++i) {
		//if not empty space
		if (user_input.at(i) != ' ') {
			if (user_input.at(i) == ';') {
				if (i != 0) { //prevents error if 2 consecutive semicolon
					//std::cout << user_input.substr(marker, i) << std::endl; DELETE AFTER DONE
					//create command object and push cmd into vector
					Terminal* cmd = new Command(user_input.substr(0, i));
					v.push_back(cmd);
					//Terminal* conn = new SemiColon();
					//v.push(conn);
					user_input = user_input.substr(i + 1);	
					//std::cout << user_input << std::endl; ----------------- DELETE AFTER DONE
				}
			}
			else if (user_input.at(i) == '&') { //TODO
				
			}
			else if (user_input.at(i) == '|') { //TODO
				
			}
			else if (user_input.at(i) == '\n') {
				//check if there is a connector
					//if connector exist, delete it
				Terminal* cmd = new Command(user_input.substr(0,i));
				v.push_back(cmd);
			}
		}
	}
};

#endif
