#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "terminal.h" //include strings
#include <iostream>
class Connector : public Terminal{
    //inherited attribute: std::string terminal_type
    protected:
        std::string connector_type;
    public:
        //constructor
        Connector() : Terminal("conn") {
        };
        
        
        //functions
        std::string getConnectorType() {
            return this->connector_type;
        };
        
        virtual void execute() = 0;
};

class And : public Connector {
    public:
        //constructor
        And() {
            connector_type = "&";
        };
	
	void execute() {
	
	};
};

class Or : public Connector {
    public:
	//constructor
	Or()  {
	    connector_type = "|";
	};

	void execute() {
	
	};
};

class SemiColon : public Connector {
    public:
	//constructor
	SemiColon() {
	    connector_type = ";";
	};
	
	void execute() {
	
	};
};
#endif
