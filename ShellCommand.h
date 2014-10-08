//
//  ShellCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__ShellCommand__
#define __toyshell__ShellCommand__

#include <iostream>
#include <string>
#include "Command.h"
#include "Shell.h"

class Shell;

using namespace std;

class ShellCommand: public Command {
public:
	ShellCommand(Shell *shell, string *parts, int wordCount);

	~ShellCommand();

	virtual bool execute() = 0;

	string getCommandString();

protected:
	string command;
	Shell *shell;
	string *parts;
	int wordCount;
};

#include "NewNameCommand.h"
#include "SetShellNameCommand.h"
#include "SetTerminatorCommand.h"
#include "SaveNamesCommand.h"
#include "ReadNamesCommand.h"
#include "PrintHistoryCommand.h"
#include "NewNamesCommand.h"

#endif /* defined(__toyshell__ShellCommand__) */
