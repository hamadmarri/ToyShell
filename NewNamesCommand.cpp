//
//  NewNamesCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "NewNamesCommand.h"

bool NewNamesCommand::execute() {

	this->shell->aliases.printList();
	return true;
}
