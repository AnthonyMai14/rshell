#include "../header/tester.h"

Tester::Tester() : Command() {}

Tester::Tester(std::vector<std::string> &parsed_cmd_line) : Command(parsed_cmd_line) {}

bool Tester::execute() {
    bool check = false;
    // Checks if the test has arguments
    if(parse_cmd.size() == 1 && parse_cmd.at(0).at(0) != '-') {
        parse_cmd.insert(parse_cmd.begin(), "-e");
    }
        
    if (parse_cmd.at(0) == "-e" || parse_cmd.at(0) == "-f" || parse_cmd.at(0) == "-d") {
        // Puts the file name into a character array
        std::string filename = parse_cmd.at(1);
        char f[1024];
        strcpy(f, filename.c_str());
        
        struct stat exist;
        
        if (parse_cmd.at(0) == "-e") {
            if (stat(f, &exist) == 0) {
                std::cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                std::cout << "(False)\n";
            }
        }
        else if (parse_cmd.at(0) == "-f") {
            if (stat(f, &exist) == 0 && S_ISREG(exist.st_mode)) {
                std::cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                std::cout << "(False)\n";
            }
        }
        else {
            if (stat(f, &exist) == 0 && S_ISDIR(exist.st_mode)) {
                std::cout << "(True)\npath exists\n";
                check = true;
            }
            else {
                std::cout << "(False)\n";
            }
        }
    }
    else {
        // Error if invalid argument
        perror("Error: Invalid flag.\n");
    }
    return check;
}