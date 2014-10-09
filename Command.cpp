/*
 * Command.cpp
 *
 *  Created on: 2014-10-08
 *      Author: hamadmarri
 */

#include "Command.h"

void Command::setCommand(string command) {
	if (command.find('$') != string::npos) {
		this->commandStr = command.substr(0, command.find('$'));
		this->commentStr = command.substr(command.find('$'),
				command.length() - 1);
	} else {
		this->commandStr = command;
	}
}

string Command::getCommandString() {
	return this->commandStr;
}

string Command::getCommentString() {
	return this->commentStr;
}
