//
//  Alias.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "Alias.h"

Alias::Alias(string alias, string command) {
	this->alias = alias;
	this->command = new SystemCommand(command);
}

Alias::~Alias() {
	delete this->command;
}

bool Alias::execute() {
	return this->command->execute();
}

string Alias::getAliasString() const {
	return this->alias;
}

string Alias::getCommandString() {
	return this->command->getCommandString();
}

bool Alias::operator!=(const Alias &rhs) {
	return (this->getAliasString() != rhs.getAliasString());
}
