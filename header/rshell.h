#ifndef RSHELL_H
#define RSHELL_H

#include "command.h"
#include "connector.h"
#include "tester.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unistd.h> //getlogin, get hostname
#include <stdlib.h> //exit()

class RShell {
    private:
		char username[100];
		char hostname[100];
		
		std::string user_input;
		std::vector<Base*> cmd_tree;
		
		void parse(std::vector<std::string> &);
		void binaryExpressionTree(std::vector<std::string> &);
		void createTree(std::stack<Connector*> &);
		void createCmd(std::vector<std::string> &, unsigned, unsigned);
		void createTester(std::vector<std::string> &, unsigned, unsigned);
		void executeCmds();
		
    public:
		RShell();
		
		void run();
};

#endif
