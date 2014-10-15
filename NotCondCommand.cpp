/*
 * NotNotCondCommand.cpp
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#include "NotCondCommand.h"

NotCondCommand::NotCondCommand(Shell *shell, string *parts, int wordCount) :
		ShellCommand(shell, parts, wordCount) {

	parseCommand(parts, wordCount);
}

void NotCondCommand::parseCommand(string *parts, int wordCount) {
	this->conditionString[0] = parts[2];
	this->conditionString[1] = parts[3];

	int cndWordCount = wordCount - 5;
	string *cndParts = new string[cndWordCount];

	for (int i = 0; i < cndWordCount; ++i)
		cndParts[i] = parts[i + 5];

	this->shell->substituteAliases(cndParts, cndWordCount);

	if (this->shell->isBuiltinCommand(cndParts[0]))
		this->conditionalCommand = this->shell->getBuiltinCommand(cndParts,
				cndWordCount);
	else {
		string line = "";
		for (int i = 0; i < cndWordCount; i++)
			line += cndParts[i] + ' ';

		this->conditionalCommand = new SystemCommand(this->shell, line);
	}

}

bool NotCondCommand::execute() {

	if (passCheck())
		return false;

	if (this->conditionalCommand != NULL)
		return this->conditionalCommand->execute();
	else
		cout << "the conditional command cannot be executed\n";

	return false;
}

bool NotCondCommand::passCheck() {
	/*
	 * CHECKE <file_name>, CHECKD <file_name>, CHECKR <file_name>, CHECKW <file_name>, and CHECKX
	 * exists, is a directory, is readable, is writable, and is executable
	 */
	string statusCheck = this->args[2];
	string filename = this->args[3];
	struct stat st;

	if (stat(filename.c_str(), &st) == 0) {
		if (statusCheck == "checke") {
			// do nothing, stat(filename.c_str(), &st) == 0 <<<< already checked that file is exists
		} else if (statusCheck == "checkd") {
			if (!S_ISDIR(st.st_mode))
				return false;
		} else if (statusCheck == "checkr") {
			if ((st.st_mode & S_IRUSR) != S_IRUSR)
				return false;
		} else if (statusCheck == "checkw") {
			if ((st.st_mode & S_IWUSR) != S_IWUSR)
				return false;
		} else if (statusCheck == "checkx") {
			if ((st.st_mode & S_IXUSR) != S_IXUSR)
				return false;
		}
	} else {
		return false;
	}

	return true;
}

