/*
 * StopCommand.cpp
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#include "StopCommand.h"

StopCommand::StopCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {
}

bool StopCommand::execute() {
	this->shell->endShell();
	return true;
}
