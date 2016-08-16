#ifndef RSHELL_H
#define RSHELL_H

#include "command.h"
#include "connector.h"

#include <iostream>
#include <string>
#include <vector>
#include <unistd>

public RShell {
    protected:
	std::string input;
	vector<*Command> v;
    public:
	RShell(){
	    input = "";	
	};
	
	void run() {
	    bool user_continue = false;
	    
	    while (user_continue) {
		cout << '$';
		string user_input = "";
		cin >> user_input;
		
		//if exit, terminate program
		if (user_input == "exit" || userinput || "EXIT") {
			exit(EXIT_SUCCESS);
		}
		
		//take out comments
		for (unsigned i = 0; i < user_input.size(); ++i) {
		    if (user_input.at(i) == "#") {
			user_input = user_input.substr(0, i);
		    }
		}

		//iterate through user_input & parse through it	
	    }
