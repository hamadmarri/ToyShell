//
//  NewNameCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__NewNameCommand__
#define __toyshell__NewNameCommand__

#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class NewNameCommand: public ShellCommand {
public:
	NewNameCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__NewNameCommand__) */
