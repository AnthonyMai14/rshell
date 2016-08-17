#ifndef RSHELL_H
#define RSHELL_H

#include "command.h"
#include "connector.h"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> //getlogin, get hostname
#include <stdlib.h> //exit()

class RShell {
    protected:
		std::string input;
		std::vector<Terminal*> v;
    public:
		RShell() : input("") {
			// char* login = getlogin();
			// int comp = gethostname(login, 100);
			
			// if(comp) {
			// 	// std::cout << "Set host name: ";
			// 	// char host[100];
			// 	// std::cin >> host;
			// 	// comp = sethostname(host, 100);
			// }
		};
		
		void run();
		void parse(std::string user_input);
		void cmdCreate(std::string user_input, unsigned i);
		void whitespace(std::string user_input, unsigned i);
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
		//std::cout << v.size() << std::endl; //------------------------DELETE AFTER DONE
		if(!v.empty()) {//if vector is not empty
			//iterator through vectors and call commands 
			for (int i = 0; i < v.size(); ++i) {
				//execute cmd
				if ( (i % 2) == 0) {
					v.at(i)->execute();
				}
				//return type
				if ( (v.size() % 2) == 0 ) {//exist a connector
					if (v.at(i)->getTerminalType() == "conn") {
						//check condition of connector
						//depending on connector go to next cmd by changing 'i'
						// std::string conn_type = v.at(i)->getConnectorType();
						// if (conn_type == "&") {
							
						// }
						// else if (conn_type == "|") {
							
						// }
						// else if (conn_type == ";" ) {
							
						// }
						//------------------------potential bug if conn doesn't exist
					}
				}
			}
			//after finish executing empty the vector for next commands
			while (!v.empty()) {
				v.pop_back();
			}
		}
    }
};

void RShell::parse(std::string user_input) {
	
	for (unsigned i = 0; i < user_input.size(); ++i) {
		//if not empty space
		if (user_input.at(i) != ' ') {
			
			if (user_input.at(i) == ';') {
				try{
					if (i + 1 == user_input.size()) {//if no other arguement
						std::runtime_error("Only 1 arguement");
					}
					if (user_input.at(i + 1) == ';') {
						std::runtime_error("Double \';\'");
					}
				}
				catch(std::runtime_error& excpt) {
					std::cout << excpt.what() << std::endl
							<< "Invalid use of \';\'" << std::endl;
					return;
				}
				
				//create command object and push cmd into vector
				cmdCreate(user_input, i);
				
				SemiColon* conn = new SemiColon();
				v.push_back(conn);
				
				whitespace(user_input ,i);
			}
			else if (user_input.at(i) == '&') { 
				try{
					if (i + 1 == user_input.size() ||
						i + 2 == user_input.size() ||
						i + 3 == user_input.size() ) {
						std::runtime_error("Only 1 arguement or spacing error");
					}
					else if (user_input.at(i + 1) != '&') {
						std::runtime_error("Single \'&\'");
					}
				}
				catch(std::runtime_error& excpt) {
					std::cout << excpt.what() << std::endl
							<< "Invalid use of \'&\'" << std::endl;
					return;
				}
				
				cmdCreate(user_input, i);
				
				And* conn = new And();
				v.push_back(conn);
				
				whitespace(user_input ,i);
			}
			else if (user_input.at(i) == '|') { //TODO
				try{
					if (i + 1 == user_input.size() ||
						i + 2 == user_input.size() ||
						i + 3 == user_input.size() ) {
						std::runtime_error("Only 1 arguement or spacing error");
					}
					else if (user_input.at(i + 1) != '|') {
						std::runtime_error("Single \'|\'");
					}
				}
				catch(std::runtime_error& excpt) {
					std::cout << excpt.what() << std::endl
							<< "Invalid use of \'|\'" << std::endl;
					return;
				}
				
				cmdCreate(user_input, i);
				
				Or* conn = new Or();
				v.push_back(conn);
				
				whitespace(user_input ,i);
			}
			else if ( (i + 1) == user_input.size() ) {//if no connectors
				//check if there is a connector
					//if connector exist, delete it
				cmdCreate(user_input, i);
				user_input = ""; //initialize to empty string
			}
		}
	}
};

void RShell::cmdCreate(std::string user_input, unsigned i) {
	Command* cmd = new Command();
	unsigned j;
	for (j = 0; user_input.at(j) != ' '; ++j) {}
	cmd->setCmd( user_input.substr(0, j) );
	cmd->setArg( user_input.substr(j + 1, i - (j+ 1) ) );
	v.push_back(cmd);
}

void RShell::whitespace(std::string user_input, unsigned i) {
	if (i + 1 == user_input.size()) {
		//if connector is at end of user_input, clear string
		user_input.clear();
	}
	else if (user_input.at(i + 1) == ' ') {
		user_input = user_input.substr(i + 2);
	}
	else {
		user_input = user_input.substr(i + 1);
	}
};

#endif
