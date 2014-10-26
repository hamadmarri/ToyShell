/*
 * PipedCommand.cpp
 *
 *  Created on: 2014-10-24
 *      Author: hamadmarri
 */

#include "PipedCommand.h"

PipedCommand::PipedCommand(Shell *shell, string *parts, int wordCount) {
	OneLine ol(" ");
	string partOfPipedCommand = "";
	string *tempParts;
	int tempWordCount;
	string input = "";
	string output = "";

	this->shell = shell;

	for (int i = 0; i < wordCount; ++i) {
		if (parts[i] == "@" && partOfPipedCommand.length() > 0) {
			output = "@";
			ol.setOneLine(partOfPipedCommand);
			tempParts = ol.getWords(tempWordCount);
			addCommandToList(tempParts, tempWordCount, input, output);
			partOfPipedCommand = "";
			input = "@";
		} else if (parts[i] == "[") {
			input = "[ " + parts[++i];
		} else if (parts[i] == "]") {
			output = "] " + parts[++i];
			ol.setOneLine(partOfPipedCommand);
			tempParts = ol.getWords(tempWordCount);
			addCommandToList(tempParts, tempWordCount, input, output);
			partOfPipedCommand = "";
			input = "";
		} else {
			partOfPipedCommand += parts[i];
		}
	}

	if (partOfPipedCommand.length() > 0) {
		ol.setOneLine(partOfPipedCommand);
		tempParts = ol.getWords(tempWordCount);
		addCommandToList(tempParts, tempWordCount, input, output);
	}

}

PipedCommand::~PipedCommand() {
}

void PipedCommand::addCommandToList(string *parts, int wordCount, string input,
		string output) {

	Command *cmd;
	CommandWithIOSpecification *cwios = new CommandWithIOSpecification();

	if (this->shell->isBuiltinCommand(parts[0])) {
		cmd = this->shell->getBuiltinCommand(parts, wordCount);
	} else {
		string line = "";
		for (int i = 0; i < wordCount; i++)
			line += parts[i] + ' ';

		cmd = new SystemCommand(this->shell, line);
	}

	cwios->cmd = cmd;
	cwios->input = input;
	cwios->output = output;

	this->commands.push_back(cwios);
}

bool PipedCommand::execute() {
	return true;
}
