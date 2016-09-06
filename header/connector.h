#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h" //include strings

//Abstract Composite Class
class Connector : public Base{
    //inherited attribute: std::string base_type
    protected:
        Base* left;
        Base* right;
        
    public:
        Connector();
        
        void setLeftChild(Base* l);
        void setRightChild(Base * r);
        virtual bool execute() = 0;
};

//Composite Class
class And : public Connector {
    public:
        And(){};
        
        bool execute();
};

class Or : public Connector {
    public:
		Or(){};
		
		bool execute();
};

class SemiColon : public Connector {
    public:
		SemiColon(){};
		
		bool execute();
};

class OpenParenthesis : public Connector {
    public:
        OpenParenthesis();
        
        bool execute();
};

#endif
