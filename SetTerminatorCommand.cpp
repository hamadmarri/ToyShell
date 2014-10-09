//
//  SetTerminatorCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "SetTerminatorCommand.h"

bool SetTerminatorCommand::execute() {
	if (wordCount < 2) {
		cout << "must type the new terminator\n";
		return false;
	}

	this->shell->terminator = args[1];
	return true;
}
