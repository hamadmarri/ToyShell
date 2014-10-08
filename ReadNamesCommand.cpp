//
//  ReadNamesCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "ReadNamesCommand.h"

bool ReadNamesCommand::execute() {
	ifstream inFile;
	OneLine ol;
	string *partsFromFile;
	int wordCountFromFile;
	string alias;
	string command = "";

	if (wordCount < 2) {
		cout << "must specify file name\n";
		return false;
	}

	inFile.open(parts[1].c_str());

	// delete old aliases
	this->shell->aliases.deleteAllItems();

	while (ol.readLine(inFile)) {
		partsFromFile = ol.getWords(wordCountFromFile);
		alias = partsFromFile[0];
		command = "";

		for (int i = 1; i < wordCountFromFile; i++) {
			command += partsFromFile[i];
			if (i < wordCountFromFile - 1)
				command += ' ';
		}

		this->shell->aliases.add(new Alias(alias, command));
	}

	inFile.close();
	return true;
}
