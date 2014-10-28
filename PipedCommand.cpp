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
	int pid;

	switch (pid = fork()) {
	case -1:
		//fork failure
		perror("Fork fail: cannot execute this command");
		return false;
		break;
	case 0: //child process
		executeChilds();
		exit(EXIT_SUCCESS);
		break;
	default: // shell process
		int status;
		//waitpid(pid, &status, WUNTRACED);
		wait(&status);
		break;
	}
	return true;
}

// cat [ main.cpp @ grep return ] file1.txt
// cat [ main.cpp @ grep s @ sort -r
// ls @ sort -r
void PipedCommand::executeChilds() {
	int fd[2];
	int outFile = -1;
	int inFile = -1;

	for (unsigned int i = 0; i < this->commands.size(); ++i) {
		CommandWithIOSpecification *cwiosParent = this->commands.at(i);
		inFile = -1;
		outFile = -1;

		// check if input from a file
		if (cwiosParent->input.size() > 0
				&& cwiosParent->input.substr(0, 1) == "[") {
			inFile = open(cwiosParent->input.substr(2).c_str(), O_RDONLY,
					S_IRUSR | S_IWUSR);
		}

		// check if output is a pipe
		if (cwiosParent->output == "@") {
			// creates a pipe here, returns error if it failed
			if (pipe(fd) == -1) {
				perror("Pipe fail");
				exit(1);
			}
			executePipe(cwiosParent, fd, inFile);
			continue;
		}

		// check if outout to a file
		if (cwiosParent->output.size() > 0
				&& cwiosParent->output.substr(0, 1) == "]") {
			outFile = open(cwiosParent->output.substr(2).c_str(),
					O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

			dup2(outFile, fileno(stdout));
		}

		// for stdout
		// check if input is set
		// copy the input file description if is set
		if (inFile != -1)
			dup2(inFile, fileno(stdin));

		cwiosParent->cmd->execute();
		exit(EXIT_SUCCESS);
	}
}

void PipedCommand::executePipe(CommandWithIOSpecification *cwiosParent,
		int fd[], int inFile) {

	int status;
	int pid;

	// Forks the program, and then operates based on if it is the child, the parent, or if the fork failed
	switch (pid = fork()) {
	case -1: //fork failure
		perror("Fork fail");
		exit(EXIT_FAILURE);
		break;
	case 0: //child process
		//copies file description of pipe output to the standard output file of the shell
		dup2(fd[IN], fileno(stdin));
		close(fd[IN]);
		close(fd[OUT]);
		break;
	default: //parent process
		// copy output descriptor
		dup2(fd[OUT], fileno(stdout));

		// copy the input file description if is set
		if (inFile != -1)
			dup2(inFile, fileno(stdin));

		close(fd[IN]);
		close(fd[OUT]);


		cwiosParent->cmd->execute();

		if (inFile != -1)
			close(inFile);

		exit(EXIT_SUCCESS);
		break;
	}
}
