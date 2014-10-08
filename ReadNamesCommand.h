//
//  ReadNamesCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__ReadNamesCommand__
#define __toyshell__ReadNamesCommand__

#include <fstream>
#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class ReadNamesCommand: public ShellCommand {
public:
	ReadNamesCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__ReadNamesCommand__) */
