//
//  BuiltInCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#ifndef __toyshell__BuiltInCommand__
#define __toyshell__BuiltInCommand__

#include <iostream>
#include <cstdlib>
#include <string>
#include "Command.h"
#include "Shell.h"

class Shell;

using namespace std;

class SystemCommand: public Command {
public:

	SystemCommand(Shell *shell, string command);
	~SystemCommand();

	bool execute();

private:
	Shell *shell;
	char** getArgv(string command);
	string* getPaths(char *path, int &size);
};

#endif /* defined(__toyshell__BuiltInCommand__) */
