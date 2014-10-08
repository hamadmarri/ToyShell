//
//  SetShellNameCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "SetShellNameCommand.h"

bool SetShellNameCommand::execute() {
	if (this->wordCount < 2) {
		cout << "must have name for the shell\n";
		return false;
	}

	this->shell->shellName = parts[1];
	return true;
}
