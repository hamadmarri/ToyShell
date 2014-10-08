//
//  NewNamesCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__NewNamesCommand__
#define __toyshell__NewNamesCommand__

#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class NewNamesCommand: public ShellCommand {
public:
	NewNamesCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__NewNamesCommand__) */
