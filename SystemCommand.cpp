//
//  BuiltInCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "SystemCommand.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <cstring>
#include "oneline.h"

extern char **environ;

SystemCommand::SystemCommand(Shell *shell, string command) {
	this->shell = shell;
	this->setCommand(command);
}

SystemCommand::~SystemCommand() {
	this->commandStr = "";
}

bool SystemCommand::execute() {

	string fileName = this->commandStr.substr(0, this->commandStr.find(" "));
	string progName = this->commandStr;
	char **argv = this->getArgv(this->commandStr);
	int pathsCount;
	string *paths = this->getPaths(getenv("PATH"), pathsCount);
	int childPid;
	int status;

	for (int i = 0; i < pathsCount; ++i) {
		string f;
		f = paths[i].c_str();
		f += "/" + fileName;

		if (access(f.c_str(), X_OK) != 0)
			continue;

		childPid = fork();

		if (childPid == 0) {
//			cout << getpid() << endl;
//			cout << fileName << endl;

			execve(f.c_str(), argv, environ);
			cout << strerror(errno) << endl;
		} else {
			wait(&status);
			return true;
		}

		break;
	}

	cout << strerror(errno) << endl;
	return false;
}

char** SystemCommand::getArgv(string command) {

	char **argv;
	string *words;
	OneLine ol(" ");
	int count;

	ol.setOneLine(command);
	words = ol.getWords(count);

	argv = new char*[count + 1];
	for (int i = 0; i < count; ++i)
		argv[i] = strdup(words[i].c_str());

	argv[count] = NULL;

	return argv;
}


string* SystemCommand::getPaths(char *path, int &size) {
	OneLine ol(":");
	ol.setOneLine(string(path));
	ol.breakLine();
	return ol.getWords(size);
}

