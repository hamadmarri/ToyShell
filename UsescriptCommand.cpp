/*
 * UsescriptCommand.cpp
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#include "UsescriptCommand.h"

UsescriptCommand::UsescriptCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {

	fileRecursionLimit = 5;
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

bool UsescriptCommand::executeCommand(OneLine &ol) {
	int wordCount;
	string* parts = ol.getWords(wordCount);
	Command *cmd;

	// check if white space or comment
	if (parts[0] == "" || parts[0] == "$")
		return true;

	// aliases subsitution
	this->shell->substituteAliases(parts, wordCount);

	// TODO: the following line should be removed it is just for testing
	if (parts[0] == "backjobs") {
		this->shell->jobs.printJobs();
		return true;
	} else if (parts[0] == "frontjob") {
		this->shell->jobs.waitForJob(atoi(parts[1].c_str()));
		return true;
	}

	if (this->shell->isPiped(parts, wordCount)) {
//		PipedCommand pc(this->shell, parts, wordCount);
//		pc.execute();
		cmd = new PipedCommand(this->shell, parts, wordCount);
	} else if (this->shell->isBuiltinCommand(parts[0])) {
//		Command *sc = this->shell->getBuiltinCommand(parts, wordCount);
//		sc->execute();
		cmd = this->shell->getBuiltinCommand(parts, wordCount);
	} else {
		string line = "";
		for (int i = 0; i < wordCount; i++)
			line += parts[i] + ' ';

//		SystemCommand s(this->shell, line);
//		s.execute();
		cmd = new SystemCommand(this->shell, line);
	}

	// check for recursion
	if (isExceedLimit(cmd))
		return false;

	return cmd->execute();
}

bool UsescriptCommand::isExceedLimit(Command *cmd) {
	if (cmd->getCommandString().length() > 8
			&& cmd->getCommandString().substr(0, 7) == "usescript") {

		if (this->fileRecursionLimit-- == 0)
			return true;
	}

	return false;
}

