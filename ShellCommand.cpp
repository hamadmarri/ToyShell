//
//  ShellCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "ShellCommand.h"

ShellCommand::ShellCommand(Shell *shell, string *parts, int wordCount) {

	// get all command line
	this->command = "";
	for (int i = 0; i < wordCount; i++) {
		this->command += parts[i];
		if (i < wordCount - 1)
			this->command += ' ';
	}

	// deep copy for parts
	this->parts = new string[wordCount];
	for (int i = 0; i < wordCount; i++)
		this->parts[i] = parts[i];

	this->shell = shell;
	this->wordCount = wordCount;
}

ShellCommand::~ShellCommand() {
	delete[] this->parts;
}

string ShellCommand::getCommandString() {
	return this->command;
}

