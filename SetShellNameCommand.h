//
//  SetShellNameCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__SetShellNameCommand__
#define __toyshell__SetShellNameCommand__

#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class SetShellNameCommand: public ShellCommand {
public:
	SetShellNameCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__SetShellNameCommand__) */
