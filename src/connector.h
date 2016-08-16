#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>

class Connector {
    protected:
        string connector_id;
    public:
        //constructor
        Connector();
        
        //virtual function
        virtual void runRshell() = 0;
}

class Add : public Connector {
    public:
        //constructor
        Add() : connector_id("&&") {};
	
	void runRshell() {
	
	};
};

class Or : public Connector {
    public:
	//constructor
	Or() : connector_id("||") {};

	void runRshell() {
	
	};
};

class SemiColon : public Connector {
    public:
	//constructor
	SemiColon : connector_id(";") {};
	
	void runRshell() {
	
	};
};
#endif
