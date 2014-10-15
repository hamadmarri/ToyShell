/*
 * StopCommand.h
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#ifndef STOPCOMMAND_H_
#define STOPCOMMAND_H_

#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class StopCommand: public ShellCommand {
public:
	StopCommand(Shell *shell, string *parts, int wordCount);
	bool execute();

};

#endif /* STOPCOMMAND_H_ */
