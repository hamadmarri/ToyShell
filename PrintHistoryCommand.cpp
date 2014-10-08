//
//  PrintHistoryCommand.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-10.
//

#include "PrintHistoryCommand.h"

bool PrintHistoryCommand::execute() {
	this->shell->invoker.printHistory();
	return true;
}
