/*
 * PipedCommand.cpp
 *
 *  Created on: 2014-10-24
 *      Author: hamadmarri
 */

#include "PipedCommand.h"

PipedCommand::PipedCommand(Shell *shell, string *parts, int wordCount) {
	Command *cmd;
	string partOfPipedCommand = "";

	this->shell = shell;

	for (int i = 0; i < wordCount; ++i) {
		if (parts[i] == "@") {
			addCommandToList(partOfPipedCommand);
			partOfPipedCommand = "";
		} else {
			partOfPipedCommand += parts[i];
		}
	}

}

PipedCommand::~PipedCommand() {
}

void PipedCommand::addCommandToList(string partOfPipedCommand) {
	if (this->shell->isBuiltinCommand(partOfPipedCommand[0]))
			this->conditionalCommand = this->shell->getBuiltinCommand(partOfPipedCommand,
					cndWordCount);
		else {
			string line = "";
			for (int i = 0; i < cndWordCount; i++)
				line += cndParts[i] + ' ';

			this->conditionalCommand = new SystemCommand(this->shell, line);
		}
}

bool PipedCommand::execute() {
	return true;
}
