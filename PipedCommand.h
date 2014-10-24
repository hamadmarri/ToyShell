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

class PipedCommand: public Command {
public:
	PipedCommand(Shell *shell, string *parts, int wordCount);
	~PipedCommand();

	bool execute();

private:

	void addCommandToList(string partOfPipedCommand);

	Shell *shell;
	vector<Command*> commands;

};

#endif /* PIPEDCOMMAND_H_ */
