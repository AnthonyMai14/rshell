#ifndef BASE_H
#define BASE_H

#include <string>

/*
* Component for class Command & Connector
*/
class Base {
    protected:
        //used to identify if it is a Command or Connector
        std::string base_type;
        
    public:
        Base() {}
        
        std::string getBaseType() { return base_type; };
        virtual bool execute() = 0;
};
#endif
