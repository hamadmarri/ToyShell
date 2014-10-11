//
//	created by Hamad Almarri
//

#include "Invoker.h"

unsigned int Invoker::maxHistory = 10;

Invoker::Invoker() {
}

Invoker::~Invoker() {
}

void Invoker::addCommand(Command *cmd) {
	if (this->commands.size() == this->maxHistory)
		this->commands.pop_front();

	this->commands.push_back(cmd);
}

bool Invoker::addAndExecuteCommand(Command *cmd) {
	addCommand(cmd);

#ifdef DEBUG_MODE
	cout << cmd->getCommentString() << endl;
#endif

	return cmd->execute();
}

bool Invoker::execute(Command *cmd) {
	// execute
	return cmd->execute();
}

bool Invoker::execute(unsigned int at) {
	Command *cmd;

	// check if at is out of range
	if (at > this->maxHistory || at > this->commands.size())
		return false;

	cmd = this->commands.at(at);

	// if command is null, then return null
	if (cmd == NULL)
		return false;

	return this->addAndExecuteCommand(cmd);
}

Command* Invoker::getCommand(unsigned int at) {
	return this->commands.at(at);
}

void Invoker::printHistory() {
	for (unsigned int i = 0; i < this->commands.size(); i++)
		cout << i + 1 << ":\t" << this->commands.at(i)->getCommandString()
				<< endl;
}

