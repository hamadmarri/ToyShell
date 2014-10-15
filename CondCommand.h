/*
 * CondCommand.h
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#ifndef CONDCOMMAND_H_
#define CONDCOMMAND_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ShellCommand.h"
#include "SystemCommand.h"

class ShellCommand;

using namespace std;

class CondCommand: public ShellCommand {
public:
	CondCommand(Shell *shell, string *parts, int wordCount);

	bool execute();

protected:
	void parseCommand(string *parts, int wordCount);
	bool passCheck();
	string conditionString[2];
	Command *conditionalCommand;
};

#endif /* CONDCOMMAND_H_ */
