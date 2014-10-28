/*
 * UsescriptCommand.cpp
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#include "UsescriptCommand.h"

UsescriptCommand::UsescriptCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {

}

// usescript script
bool UsescriptCommand::execute() {

	string line;
	ifstream inFile;
	OneLine ol(" ");

	if (wordCount < 2) {
		cout << "must specify the file name\n";
		return false;
	}

	inFile.open(this->args[1].c_str());

	// prime reading
	getline(inFile, line);

	while (inFile) {
		ol.setOneLine(line);
		executeCommand(ol);

		// next read
		getline(inFile, line);
	}

	inFile.close();
	return true;
}

void UsescriptCommand::executeCommand(OneLine &ol) {
	int wordCount;
	string* parts = ol.getWords(wordCount);

	// check if white space or comment
	if (parts[0] == "" || parts[0] == "$")
		return;

	// aliases subsitution
	this->shell->substituteAliases(parts, wordCount);

	// TODO: the following line should be removed it is just for testing
	if (parts[0] == "backjobs") {
		this->shell->jobs.printJobs();
		return;
	} else if (parts[0] == "frontjob") {
		this->shell->jobs.waitForJob(atoi(parts[1].c_str()));
		return;
	}

	if (this->shell->isPiped(parts, wordCount)) {
		PipedCommand pc(this->shell, parts, wordCount);
		pc.execute();
	} else if (this->shell->isBuiltinCommand(parts[0])) {
		Command *sc = this->shell->getBuiltinCommand(parts, wordCount);
		sc->execute();
	} else {
		string line = "";
		for (int i = 0; i < wordCount; i++)
			line += parts[i] + ' ';

		SystemCommand s(this->shell, line);
		s.execute();
	}
}
