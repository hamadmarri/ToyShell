/*
 * PipedCommand.h
 *
 *  Created on: 2014-10-24
 *      Author: hamadmarri
 */

#ifndef PIPEDCOMMAND_H_
#define PIPEDCOMMAND_H_

#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Command.h"
#include "Shell.h"

#define IN 0
#define OUT 1

class Shell;

using namespace std;


class CommandWithIOSpecification {
public:
	CommandWithIOSpecification() {
		this->cmd = NULL;
		this->input = "";
		this->output = "";
	}
	Command *cmd;
	string input;
	string output;
};

class PipedCommand: public Command {
public:
	PipedCommand(Shell *shell, string *parts, int wordCount);
	~PipedCommand();

	bool execute();

private:

	void addCommandToList(string *parts, int wordCount, string input, string output);
	void executeChilds();
	void executePipe(CommandWithIOSpecification *cwiosParent, int fd[], int inFile);

	Shell *shell;
	vector<CommandWithIOSpecification*> commands;

};

#endif /* PIPEDCOMMAND_H_ */
