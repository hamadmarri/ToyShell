//
//  PrintHistoryCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__PrintHistoryCommand__
#define __toyshell__PrintHistoryCommand__

#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class PrintHistoryCommand: public ShellCommand {
public:
	PrintHistoryCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__PrintHistoryCommand__) */
