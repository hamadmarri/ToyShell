//
//  BuiltInCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "SystemCommand.h"

SystemCommand::SystemCommand(string command) {
	this->setCommand(command);
}

SystemCommand::~SystemCommand() {
	this->commandStr = "";
}

bool SystemCommand::execute() {
	return !system(this->commandStr.c_str());
}

