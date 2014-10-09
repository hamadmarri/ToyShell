//
//  Alias.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "Alias.h"

Alias::Alias(string alias, string commandStr) {
	this->alias = alias;

	this->setCommand(commandStr);

	this->command = new SystemCommand(this->commandStr);
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

bool Alias::operator!=(const Alias &rhs) {
	return (this->getAliasString() != rhs.getAliasString());
}
