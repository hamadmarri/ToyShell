/*
 * Display.cpp
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#include "DisplayCommand.h"

DisplayCommand::DisplayCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {

}

bool DisplayCommand::execute() {
	cout << this->getCommandString().substr(8) << endl;
	return true;
}
