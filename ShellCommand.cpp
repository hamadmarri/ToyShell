//
//  ShellCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "ShellCommand.h"

ShellCommand::ShellCommand(Shell *shell, string *parts, int wordCount) {

	string tempCommand = "";

	// get all command line
	for (int i = 0; i < wordCount; i++) {
		tempCommand += parts[i];
		if (i < wordCount - 1)
			tempCommand += ' ';
	}

	// deep copy for parts
	this->args = new string[wordCount];
	for (int i = 0; i < wordCount; i++) {
		// TODO: might be right before the word like $anything
		if (parts[i] == "$")
			break;

		this->args[i] = parts[i];
	}

	this->setCommand(tempCommand);
	this->shell = shell;
	this->wordCount = wordCount;
}

ShellCommand::~ShellCommand() {
	delete[] this->args;
}

