//
//  NewNameCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "NewNameCommand.h"

bool NewNameCommand::execute() {
	Alias *als;
	if (wordCount < 2) {
		cout << "must specify the alias name\n";
		return false;
	} else if (this->shell->isBuiltinCommand(args[1])) {
		cout << "cannot make an alias has the same name of a built-in command\n";
		return false;
	} else if (wordCount < 3) {
		als = new Alias(args[1], "");
		this->shell->aliases.deleteItem(als);
		delete als;
	} else if (wordCount >= 3) {
		string alias = args[1];
		string command = "";

		for (int i = 2; i < wordCount; i++)
			command += args[i] + ' ';

		als = new Alias(alias, command);
		if (this->shell->aliases.find(alias))
			this->shell->aliases.deleteItem(als);

		this->shell->aliases.add(als);
	}

	return true;
}

