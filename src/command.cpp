#include "command.h"

//--------------------------------------------------------------------------
// Leaf Node
//--------------------------------------------------------------------------
Command::Command() : Base() {
	base_type = "cmd";
}

Command::Command(std::vector<std::string> &parse_cmd) : Base() {
	base_type = "cmd";
	//set pointer to 
	this->parse_cmd = parse_cmd;
}

//Private Functions
void Command::exitFlag() {
	if (parse_cmd.size() == 1 && parse_cmd.at(0) == "exit") {
        exit(0);
    }
}

void Command::createCharPointer() {
	cmd_line.resize(parse_cmd.size() + 1);
	for (unsigned i = 0; i != parse_cmd.size(); ++i) {
		cmd_line[i] = &parse_cmd[i][0]; //------------------TODO
	}
}

bool Command::callFork() {
	pid_t pid = fork();
    if (pid < 0) {
        //fork failed to execute
        perror("Forking Failed: ");
        parse_cmd.clear();
        exit(1);
    }
    if (pid == 0) {
        // child process
        if (execvp(cmd_line[0], cmd_line.data()) == -1) {
            //failed to execute
            perror("Command not found: ");
            exit(1);
        }
    }
    if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);

        if (WEXITSTATUS(status) == 0) {
            return true;
        }
        else if (WEXITSTATUS(status) == 1) {
            return false;
        }
    }
    return true;
}

//Public Functions
bool Command::execute() {
	//if keyword "exit" exist, terminate program
	exitFlag();
	//vector<char*> cmd_line points to the first 
	//characters at each index in vector<string>parse_cmd
	createCharPointer();
	//call fork
	return callFork();
}