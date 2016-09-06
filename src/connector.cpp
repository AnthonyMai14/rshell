#include "../header/connector.h"

//--------------------------------------------------------------------------
// Connector Class
//--------------------------------------------------------------------------
Connector::Connector() : Base() {
    base_type = "conn";
}
void Connector::setLeftChild(Base* l) {
    left = l;
}
void Connector::setRightChild(Base * r) { 
    right = r; 
}

//--------------------------------------------------------------------------
// And Class
//--------------------------------------------------------------------------
bool And::execute() {
    return (left->execute() && right->execute());
}

//--------------------------------------------------------------------------
// Or Class
//--------------------------------------------------------------------------
bool Or::execute() {
    return (left->execute() || right->execute());
}

//--------------------------------------------------------------------------
// SemiColon Class
//--------------------------------------------------------------------------
bool SemiColon::execute() {
    bool temp = left->execute();
    temp = right->execute();
    return temp;
}