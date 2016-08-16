#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

/*
* Component for class Command & Connector
*/
class Terminal {
    protected:
        std::string terminal_type;
    public:
        //constructor
        Terminal(std::string tt) : terminal_type(tt) {};
        
        //function
        std::string getTerminalType() {
            return terminal_type;
        };
};
#endif