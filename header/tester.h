#ifndef TESTER_H
#define TESTER_H

#include "command.h"

#include <unistd.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <iostream>

class Tester : public Command{
    public:
        Tester();
        Tester(std::vector<std::string> &);
        bool execute();
};

#endif