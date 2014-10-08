//
//  Shell.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "Shell.h"

Shell::Shell() {
	this->shellName = "toyshell";
	this->terminator = "->";
	this->numberOfCommands = 1;

	// initialize builtin commands
	this->builtinCommands[0] = "stop";
	this->builtinCommands[1] = "setshellname";
	this->builtinCommands[2] = "setterminator";
	this->builtinCommands[3] = "history";
	this->builtinCommands[4] = "!";
	this->builtinCommands[5] = "newname";
	this->builtinCommands[6] = "newnames";
	this->builtinCommands[7] = "savenewnames";
	this->builtinCommands[8] = "readnewnames";
}

void Shell::startShell() {
	OneLine ol;

	printWelcomPage();

	// print prompt
	cout << shellName << "[" << numberOfCommands << "]" << terminator << ' ';

	while (ol.readLine(cin)
			&& ol.getFirstWord() != builtinCommands[BuiltinCommandsEnum::STOP]) {

		// execute command
		executeCommand(ol);

		// print prompt
		cout << shellName << "[" << ++numberOfCommands << "]" << terminator
				<< ' ';
	}

	endShell();
}

void Shell::executeCommand(OneLine &ol) {
	int wordCount;
	string* parts = ol.getWords(wordCount);

	if (parts[0] == "")
		return;

	// aliases subsitution
	substituteAliases(parts, wordCount);

	if (isBuiltinCommand(parts[0])) {
		executeBuiltinCommand(parts, wordCount);
	} else {
		string line = "";
		for (int i = 0; i < wordCount; i++)
			line += parts[i] + ' ';

		executeSystemCommand(line);
	}
}

void Shell::substituteAliases(string *parts, int wordCount) {
	OneLine ol;
	string *subParts;
	int subWordCount;

	for (int i = 0; i < wordCount; i++) {

		// check if command is newname, do not susitute for the first argument
		if (i == 1 && parts[0] == builtinCommands[BuiltinCommandsEnum::NEWNAME])
			break;

		if (isAlias(parts[i])) {
			ol.setOneLine(aliases.find(parts[i])->getCommandString());
			subParts = ol.getWords(subWordCount);

			// recursive subsitution
			substituteAliases(subParts, subWordCount);

			parts[i] = "";
			for (int j = 0; j < subWordCount; j++) {
				parts[i] += subParts[j];
				if (j < subWordCount - 1)
					parts[i] += ' ';
			}

		}
	}
}

void Shell::executeBuiltinCommand(string *parts, int wordCount) {

	ShellCommand *cmd = NULL;

	if (parts[0] == builtinCommands[BuiltinCommandsEnum::STOP]) {
		endShell();
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::SETSHELLNAME]) {
		cmd = new SetShellNameCommand(this, parts, wordCount);
	} else if (parts[0]
			== builtinCommands[BuiltinCommandsEnum::SETTERMINATOR]) {
		cmd = new SetTerminatorCommand(this, parts, wordCount);
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::HISTORY]) {
		cmd = new PrintHistoryCommand(this, parts, wordCount);
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::EXCLAMATION]) {
		if (wordCount < 2) {
			cout << "must specify the number of history command\n";
			return;
		}

		istringstream buffer(parts[1]);
		int value;
		buffer >> value;
		if (!invoker.execute(value - 1))
			cout << "error: the number is out of range, use 'history' to double check\n";

	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::NEWNAME]) {
		cmd = new NewNameCommand(this, parts, wordCount);
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::NEWNAMES]) {
		cmd = new NewNamesCommand(this, parts, wordCount);
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::SAVENEWNAMES]) {
		cmd = new SaveNamesCommand(this, parts, wordCount);
	} else if (parts[0] == builtinCommands[BuiltinCommandsEnum::READNEWNAMES]) {
		cmd = new ReadNamesCommand(this, parts, wordCount);
	}

	if (cmd)
		this->invoker.addAndExecuteCommand(cmd);
}

void Shell::executeSystemCommand(string line) {
	Command *cmd = new SystemCommand(line);
	this->invoker.addAndExecuteCommand(cmd);
}

bool Shell::isBuiltinCommand(string &command) {
	for (int i = 0; i < 9; i++)
		if (command == builtinCommands[i])
			return true;

	return false;
}

bool Shell::isAlias(string &command) {
	return (aliases.find(command) != NULL);
}

void Shell::printWelcomPage() {
	cout << "Welcom to toyshell\n" << "Builtin Commands: ";
	for (int i = 0; i < 9; i++)
		cout << builtinCommands[i] << " ";

	cout << endl;
}

void Shell::endShell() {
	cout << "bye\n";
}


