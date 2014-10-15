/*
 * ExclamationCommand.cpp
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#include "ExclamationCommand.h"

ExclamationCommand::ExclamationCommand(Shell *shell, string *parts,
		int wordCount) :
		ShellCommand(shell, parts, wordCount) {
}

bool ExclamationCommand::execute() {
	if (wordCount < 2) {
		cout << "must specify the number of history command\n";
		return false;
	}

	istringstream buffer(args[1]);
	int value;
	buffer >> value;
	if (!this->shell->invoker.execute(value - 1)) {
		cout
				<< "error: the number is out of range, use 'history' to double check\n";
		return false;
	}

	return true;
}
