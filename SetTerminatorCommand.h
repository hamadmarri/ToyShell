//
//  SetTerminatorCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__SetTerminatorCommand__
#define __toyshell__SetTerminatorCommand__

#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class SetTerminatorCommand: public ShellCommand {
public:
	SetTerminatorCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__SetTerminatorCommand__) */
