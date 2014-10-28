/*
 * CullCommand.cpp
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#include "CullCommand.h"

CullCommand::CullCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {
}

bool CullCommand::execute() {

	if(wordCount < 2) {
		cout << "job number should be specified\n";
		return false;
	}

	this->shell->jobs.killJob(atoi(this->args[1].c_str()));
	return true;
}
