#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "terminal.h" //include strings

class Connector : public Terminal{
    //inherited attribute: std::string terminal_type
    public:
        //constructor
        Connector();
        
        //virtual function
        virtual string getTerminalType() = 0;
        virtual void runRshell() = 0;
}

class Add : public Connector {
    public:
        //constructor
        Add() : Terminal("&") {};
	
	void runRshell() {
	
	};
};

class Or : public Connector {
    public:
	//constructor
	Or() : Terminal("|") {};

	void runRshell() {
	
	};
};

class SemiColon : public Connector {
    public:
	//constructor
	SemiColon : Terminal(";") {};
	
	void runRshell() {
	
	};
};
#endif
