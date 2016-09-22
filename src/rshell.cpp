#include "../header/rshell.h"

//--------------------------------------------------------------------------
// Client
//--------------------------------------------------------------------------
RShell::RShell() {
    for (unsigned i = 0; i < 100; ++i)
    {
        //initialize the vectors
        username[i] = 0;
        hostname[i] = 0;
    }
    
    getlogin_r(username, 100);
    gethostname(hostname, 100);
}

void RShell::run() {
    while (1) {
		std::cout << username << "@" << hostname << '$'; 
		std::getline(std::cin, user_input);
        //create vector to store a strings 
        std::vector<std::string> parsed_input;
		//iterate through user_input & parse through it
		parse(parsed_input);
		
		binaryExpressionTree(parsed_input);
        
        executeCmds();
        
        cmd_tree.clear();
        user_input = "";
    }
}

void RShell::parse(std::vector<std::string> &parsed_input) {
    
    //allow for ';' to be parsed using strtok() by adding ' ' before it
    bool not_in_quotes = true;
    for (unsigned i = 0; i < user_input.size(); ++i) {
        //checks to see if quotes exist. If exist, will ignore parenthesis
        //within the quotes
        if (user_input.at(i) == '\"') {
            not_in_quotes = !not_in_quotes; //toggle not_in_quotes
        }
        //if not_in_quotes == 1, valid connector OR parenthesis
        //if conn/parath found, insert ' ' before or after for parsing below
        if (not_in_quotes) {
           if (user_input.at(i) == ';' || 
                user_input.at(i) == ')' ||
                user_input.at(i) == ']') {
                user_input.insert(i, " ");
                //++i will skip the conn/parath when checking value in next
                //iteration of for-loop
                ++i;
            }
            else if (user_input.at(i) == '(' ||
                        user_input.at(i) == '[') {
                user_input.insert(i + 1, " "); 
                //++i will skip the conn/parath when checking value in next
                //iteration of for-loop
                ++i; 
            }
        }
    }
    
    
    //convert string user_input to char
    char char_user_input[1024];
    strcpy(char_user_input, user_input.c_str());
    
    //begin parsing user_input and store in parsed_input using strtok
    char *ptr;
    //parse white space
    ptr = strtok(char_user_input, " "); 
    //store parsed commands into parsed_input
    while (ptr != NULL) {
        parsed_input.push_back(ptr);
        ptr = strtok(NULL, " ");
    }
}

void RShell::binaryExpressionTree(std::vector<std::string> &parsed_input) {
    // push elements from parsed_input to cmd_tree until hitting a connector
    // then execute everything before connector and clear
    // check for connector and execute next command depending on connector and if the last command pass/failed
    
    const std::string a = "&&";
    const std::string o = "||";
    const std::string s = ";";
    const std::string op = "(";
    const std::string cp = ")";
    const std::string ob = "[";
    const std::string cb = "[";
    
    //create stack to store operator. Convert infix to postfix
    std::stack<Connector*> cmd_stack; 
    
    // comment case
    for (unsigned j = 0; j < parsed_input.size(); ++j) {
        if ((parsed_input.at(j))[0] == '#') {
            parsed_input.resize(j);
            break;
        }
    }
    
    unsigned i;
    for (i = 0; i < parsed_input.size();++i) {
        // Transferring Commands
        std::string indexString = parsed_input.at(i);
        
        
        //connectors & commands
        if (parsed_input.at(i) == a) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new And());
        }
        else if (parsed_input.at(i) == o) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new Or());
        }
        else if (parsed_input.at(i) == s) {
            //check to see if exist a conn
            createTree(cmd_stack);
            //push new operator onto stack
            cmd_stack.push(new SemiColon());
        }
        else if (parsed_input.at(i) == cp) {
            //keep create tree until find open parenthesis
            while (cmd_stack.top()->getBaseType() != op) {
                createTree(cmd_stack);
            }
            cmd_stack.pop();
        }
        else if (parsed_input.at(i) == op) {
            cmd_stack.push(new OpenParenthesis());
        }
        else if (parsed_input.at(i) == "test") {
            unsigned size = parsed_input.size();
                        
            if ((i + 1) == size) {
                perror("No statement after test\n");
                //do something with exit
            }
            if ((i + 2) == size ||
                (i + 3) == size) {
                    createTester(parsed_input, i + 1, size);
                    if ((i + 2) == size) {
                        ++i;
                    }
                    else {
                        i += 2;
                    }
            }
            else if (parsed_input.at(i + 2) == a || 
                parsed_input.at(i + 2) == o ||
                parsed_input.at(i + 2) == s ) {
                    //create Tester() with default flag
                    createTester(parsed_input, i + 1, i + 2);
                    ++i; //to push conn
            }
            else if (parsed_input.at(i + 3) == a || 
                    parsed_input.at(i + 3) == o ||
                    parsed_input.at(i + 3) == s ) {
                        //create Tester with flag
                        createTester(parsed_input, i + 1, i + 3);
                        i += 2; //to push conn
            }
            else {
                perror("Invalid test statement\n");
            }
        }
        else if (parsed_input.at(i) == ob) {
             unsigned size = parsed_input.size();
             
            if ((i + 1) == size) {
                perror("No statement after test\n");
                //do something with exit
            }
            
            if (parsed_input.at(i + 3) == "]") {
                //create Tester() with default flag
                createTester(parsed_input, i + 1, i + 2);
                i += 3; //skip  "]"
            }
            else if (parsed_input.at(i + 4) == "]") {
                //create Tester with flag
                createTester(parsed_input, i + 1, i + 3);
                i += 4; //skip "]"
            }
            else {
                perror("Invalid #of statements or no ']' found\n");
            }
        }
        else {//is part of the bash cmds
            //iterate until find a conn
            unsigned j = 0;
            for (j = i; j < parsed_input.size(); ++j) {
                //if conn found
                if (parsed_input.at(j) == a || 
                    parsed_input.at(j) == o ||
                    parsed_input.at(j) == s ||
                    parsed_input.at(j) == cp) {
                        //store strings into new Fork
                        createCmd(parsed_input, i, j);
                        i = j - 1; //need to add the conn
                        break;
                }
            }
            //if no conn found, means end of cmd_vector
            if (j >=  parsed_input.size()) {
                //create new Fork
                createCmd(parsed_input, i, j);
                break;
            }
        }
    }
    
    while (!cmd_stack.empty()) {
        createTree(cmd_stack);
    }
}


void RShell::createTree(std::stack<Connector*> &cmd_stack) {
    if (!cmd_stack.empty() && (cmd_stack.top()->getBaseType() == "conn")) {
        //setRightChild
        cmd_stack.top()->setRightChild(cmd_tree.back());
        cmd_tree.pop_back();
        //setLeftChild
        cmd_stack.top()->setLeftChild(cmd_tree.back());
        cmd_tree.pop_back();
        //pop from stack & push onto cmd_tree
        cmd_tree.push_back(cmd_stack.top());
        cmd_stack.pop();
    }
    //else-if getBaseType() == "(") { //do nothing }
}

void RShell::createCmd(std::vector<std::string> &parsed_input, unsigned i, unsigned j) {
    //----------------------TODO-----------FIX ME.......quote issue, need so that quote needs to be closed in 2nd arguement
    //if just "echo"...aborts....fix!!!
    std::vector<std::string> parsed_cmd;
    for (unsigned k = i; k < j; ++k) {
        //quotes should only appear on second index
        //if not, will cause error when running cmd in excvp (command.cpp)
        //std::cout << parsed_input.at(k) << " " << k << std::endl;
        if (parsed_input.at(k) == "echo") {
            parsed_cmd.push_back(parsed_input.at(k));
            ++k;
            std::string &temp = parsed_input.at(k);
            for (unsigned l = 0; l < temp.size(); ++l) {
                if (temp.at(l) == '"') {
                    temp.erase(temp.begin() + l);
                    //std::cout << "quote..." << std::endl;
                }
            }
        }
        //push strings of parsed_input into parsed_cmd
        parsed_cmd.push_back(parsed_input.at(k));
    }
    cmd_tree.push_back(new Command(parsed_cmd));
}

void RShell::createTester(std::vector<std::string> &parsed_input, unsigned i, unsigned j) {
    std::vector<std::string> parsed_test_cmd;
    for (unsigned k = i; k < j; ++k) {
        parsed_test_cmd.push_back(parsed_input.at(k));
    }
    cmd_tree.push_back(new Tester(parsed_test_cmd));
}
void RShell::executeCmds() {
    if (!cmd_tree.empty() && cmd_tree.at(0)->execute() ) {
        //do nothing.. because already execute
    }
}