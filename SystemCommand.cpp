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
#include <cstring>
#include "oneline.h"

SystemCommand::SystemCommand(string command) {
	this->setCommand(command);
}

SystemCommand::~SystemCommand() {
	this->commandStr = "";
}

bool SystemCommand::execute() {

	string path = "/bin/"
			+ this->commandStr.substr(0, this->commandStr.find(" "));
	string progName = this->commandStr;
	char **argv = this->getArgv(this->commandStr);
	int childPid;
	int status;


	childPid = fork();

	if (childPid == 0) {
		cout << getpid() << endl;
		cout << path << endl;
		execv(path.c_str(), argv);
	} else
		wait(&status);

	return true;
}

char** SystemCommand::getArgv(string command) {

	char **argv;
	string *words;
	OneLine ol;
	int count;

	ol.setOneLine(command);
	words = ol.getWords(count);

	argv = new char*[count + 1];
	for (int i = 0; i < count; ++i)
		argv[i] = strdup(words[i].c_str());

	argv[count] = NULL;

	return argv;
}

