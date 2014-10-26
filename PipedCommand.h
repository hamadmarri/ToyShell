/*
 * PipedCommand.h
 *
 *  Created on: 2014-10-24
 *      Author: hamadmarri
 */

#ifndef PIPEDCOMMAND_H_
#define PIPEDCOMMAND_H_

#include <vector>
#include "Command.h"
#include "Shell.h"

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

	Shell *shell;
	vector<CommandWithIOSpecification*> commands;

};

#endif /* PIPEDCOMMAND_H_ */
