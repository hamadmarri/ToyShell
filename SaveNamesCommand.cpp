//
//  SaveNamesCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "SaveNamesCommand.h"

bool SaveNamesCommand::execute() {
	ofstream outFile;
	Alias *alias;

	if (wordCount < 2) {
		cout << "must specify file name\n";
		return false;
	}

	outFile.open(args[1].c_str());

	for (unsigned long i = 0; i < this->shell->aliases.getLength(); i++) {
		alias = this->shell->aliases.at(i);
		outFile << alias->getAliasString() << ' ' << alias->getCommandString()
				<< endl;
	}

	outFile.close();

	return true;
}
