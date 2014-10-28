//
//  Shell.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#ifndef __toyshell__Shell__
#define __toyshell__Shell__

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "oneline.h"
#include "Invoker.h"
#include "SystemCommand.h"
#include "ShellCommand.h"
#include "PipedCommand.h"
#include "LinkedList.h"
#include "Jobs.h"
#include <cstdlib>

class LinkedList;

using namespace std;


#define NUM_OF_BLTIN_COMMANDS 16

namespace BuiltinCommandsEnum {
enum BuiltinCommandsEnum {
	STOP,
	SETSHELLNAME,
	SETTERMINATOR,
	HISTORY,
	EXCLAMATION,
	NEWNAME,
	NEWNAMES,
	SAVENEWNAMES,
	READNEWNAMES,
	BACKJOBS,
	FRONTJOB,
	COND,
	NOT_COND,
	DISPLAY,
	USE_SCRIPT,
	CULL
};
}

class Shell {
public:
	Shell();
	~Shell();

	void startShell();
	void endShell();

private:
	void printWelcomPage();
	void executeCommand(OneLine &ol);
	void executeBuiltinCommand(string *parts, int wordCount);
	Command* getBuiltinCommand(string *parts, int wordCount);
	void executeSystemCommand(string line);
	bool isBuiltinCommand(string &command);
	void substituteAliases(string *parts, int wordCount);
	bool isAlias(string &command);
	bool isPiped(string *parts, int wordCount);
	void executePipedCommand(string *parts, int wordCount);

	int builtinCommandsCount;
	string shellName;
	string terminator;
	unsigned int numberOfCommands;
	string builtinCommands[NUM_OF_BLTIN_COMMANDS];
	Invoker invoker;
	LinkedList *aliases;
	Jobs jobs;

	friend class NewNameCommand;
	friend class SetShellNameCommand;
	friend class SetTerminatorCommand;
	friend class SaveNamesCommand;
	friend class ReadNamesCommand;
	friend class PrintHistoryCommand;
	friend class NewNamesCommand;
	friend class ExclamationCommand;
	friend class StopCommand;
	friend class SystemCommand;
	friend class CondCommand;
	friend class NotCondCommand;
	friend class PipedCommand;
	friend class DisplayCommand;
	friend class UsescriptCommand;
	friend class CullCommand;
};

#endif /* defined(__toyshell__Shell__) */
