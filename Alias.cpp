//
//  Alias.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "Alias.h"

Alias::Alias(Shell *shell, string alias, string commandStr) {
	this->shell = shell;
	this->alias = alias;

	this->setCommand(commandStr);

	this->command = new SystemCommand(shell, this->commandStr);
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
