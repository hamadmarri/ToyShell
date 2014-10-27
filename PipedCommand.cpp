/*
 * PipedCommand.cpp
 *
 *  Created on: 2014-10-24
 *      Author: hamadmarri
 */

#include "PipedCommand.h"

// cat [ main.cpp @ grep return ] file1.txt

PipedCommand::PipedCommand(Shell *shell, string *parts, int wordCount) {
	OneLine ol(" ");
	string partOfPipedCommand = "";
	string *tempParts;
	int tempWordCount;
	string input = "";
	string output = "";

	this->shell = shell;

	for (int i = 0; i < wordCount; ++i) {
		if (parts[i] == "@") { // && partOfPipedCommand.length() > 0) {
			output = "@";
			ol.setOneLine(partOfPipedCommand);
			tempParts = ol.getWords(tempWordCount);
			addCommandToList(tempParts, tempWordCount, input, output);
			partOfPipedCommand = "";
			output = "";
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
			output = "";
		} else {
			partOfPipedCommand += parts[i] + " ";
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

	switch (fork()) {
	case -1:
		//fork failure
		perror("Fork fail");
		exit(2);
		break;
	case 0: //child process
		executeChilds();
		break;
	default: // shell process
		int status;
		int pid;
		while ((pid = wait(&status)) != -1)
			cout << "job with pid = " << pid << " has been completed" << endl;
		break;
	}
	return true;
}

void PipedCommand::executeChilds() {
	int fd[2];
	int outFile = -1;
	int inFile = -1;

	for (unsigned int i = 0; i < this->commands.size(); ++i) {
		CommandWithIOSpecification *cwiosParent = this->commands.at(i);
		inFile = -1;
		outFile = -1;

		// check if input from a file
		if (cwiosParent->input.substr(0, 1) == "[") {
			inFile = open(cwiosParent->output.substr(2).c_str(), O_RDONLY,
					S_IRUSR | S_IWUSR);
		}
		// check if output is a pipe
		else if (cwiosParent->output == "@") {
			// creates a pipe here, returns error if it failed
			if (pipe(fd) == -1) {
				perror("Pipe fail");
				exit(1);
			}
			executePipe(cwiosParent, fd, inFile);
		}

		// check if outout to a file
		else if (cwiosParent->output.substr(0, 1) == "]") {
			outFile = open(cwiosParent->output.substr(2).c_str(),
					O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

			dup2(outFile, fileno(stdout));
		}
	}
}

void PipedCommand::executePipe(CommandWithIOSpecification *cwiosParent,
		int fd[], int inFile) {

	OneLine ol(" ");
	string *parts;
	int wordCount;
	char **parentArgs;

	switch (fork()) // Forks the program, and then operates based on if it is the child, the parent, or if the fork failed
	{
	case -1: //fork failure
		perror("Fork fail");
		exit(2);
		break;
	case 0: //child process
		dup2(fd[IN], fileno(stdin)); //copies file description of pipe output to the standard output file of the shell
		close(fd[IN]);
		close(fd[OUT]);
		execvp(parentArgs[0], parentArgs); //where does the output of last go? stdout normally, but write end of pipe
		exit(3);
		break;
	default: //parent process

		// copy output descriptor
		dup2(fd[OUT], fileno(stdout));

		if (inFile != -1)
			dup2(inFile, fileno(stdin));

		close(fd[IN]);
		close(fd[OUT]);

		ol.setOneLine(cwiosParent->cmd->getCommandString());
		parts = ol.getWords(wordCount);
		parentArgs = new char*[wordCount + 1];

		for (int i = 0; i < wordCount; ++i)
			parentArgs[i] = strdup(parts[i].c_str());

		parentArgs[wordCount] = NULL;

		execvp(parentArgs[0], parentArgs); // where is sort getting input from ?stdin normally, but read end of pipe

		if (inFile != -1)
			close(inFile);

		exit(4);
		break;
	}
}
