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
#include "sstream"
#include <cstring>
#include "oneline.h"
#include "Invoker.h"
#include "SystemCommand.h"
#include "ShellCommand.h"
#include "LinkedList.h"
#include "Jobs.h"
#include <cstdlib>


class LinkedList;

using namespace std;

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
	READNEWNAMES
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
	void executeSystemCommand(string line);
	bool isBuiltinCommand(string &command);
	void substituteAliases(string *parts, int wordCount);
	bool isAlias(string &command);

	string shellName;
	string terminator;
	unsigned int numberOfCommands;
	string builtinCommands[9];
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
	friend class SystemCommand;
};

#endif /* defined(__toyshell__Shell__) */
