#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "terminal.h" //include strings

class Connector : public Terminal{
    //inherited attribute: std::string terminal_type
    protected:
        std::string connector_type;
    public:
        //constructor
        Connector() : Terminal("conn") {};
        
        //virtual function
        void runRshell();
        
        //functions
        std::string getConnectorType() {
            return this->connector_type;
        };
};

class Add : public Connector {
    public:
        //constructor
        Add() : Connector(), connector_type("&") {};
	
	void runRshell() {
	
	};
};

class Or : public Connector {
    public:
	//constructor
	Or() : connector_type("|") {};

	void runRshell() {
	
	};
};

class SemiColon : public Connector {
    public:
	//constructor
	SemiColon :  connector_type(";") {};
	
	void runRshell() {
	
	};
};
#endif
