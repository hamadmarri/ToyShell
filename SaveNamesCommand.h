//
//  SaveNamesCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#ifndef __toyshell__SaveNamesCommand__
#define __toyshell__SaveNamesCommand__

#include <fstream>
#include <string>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;

class SaveNamesCommand: public ShellCommand {
public:
	SaveNamesCommand(Shell *shell, string *parts, int wordCount) :
			ShellCommand(shell, parts, wordCount) {
	}
	;
	bool execute();
};

#endif /* defined(__toyshell__SaveNamesCommand__) */
