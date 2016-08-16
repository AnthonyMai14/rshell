#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>

public Connector {
    protected:
        string connector_id;
    public:
        //constructor
        Connector();
        
        //virtual function
        virtual void runRshell() = 0;
}

public Add : public Connector {
    public:
        //constructor
        Add() : connector_id("&&") {};
	
	void runRshell() {
	
	};
};

public Or : public Connector {
    public:
	//constructor
	Or() : connector_id("||") {};

	void runRshell() {
	
	};
};

public SemiColon : public Connector {
    public:
	//constructor
	SemiColon : connector_id(";") {};
	
	void runRshell() {
	
	};
};
#endif
