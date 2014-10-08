//
//  BuiltInCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "SystemCommand.h"

SystemCommand::SystemCommand(string command) {
	this->command = command;
}

SystemCommand::~SystemCommand() {
	this->command = "";
}

bool SystemCommand::execute() {
	return !system(this->command.c_str());
}

string SystemCommand::getCommandString() {
	return this->command;
}
