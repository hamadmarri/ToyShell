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

using namespace std;

class SystemCommand: public Command {
public:

	SystemCommand(string command);
	~SystemCommand();

	bool execute();

private:
	char** getArgv(string command);
	char** getEnv();
	string* getPaths(char *path, int &size);

};

#endif /* defined(__toyshell__BuiltInCommand__) */
