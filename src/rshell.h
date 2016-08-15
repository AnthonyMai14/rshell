#ifndef RSHELL_H
#define RSHELL_H

#include "command.h"
#include "connector.h"

#include <string>

public RShell {
    protected:
	string input;
	vector<*Command> v;
    public:
	RShell() : input("") {};
	
	void run() {
	    bool user_continue = false;
	    
	    while (user_continue) {
		cout << '$';
		string user_input = "";
		cin >> user_input;
		
		//if exit, terminate program
		
		//iterate through user_input & parse through it 
	    }
