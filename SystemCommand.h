//
//  BuiltInCommand.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#ifndef __toyshell__BuiltInCommand__
#define __toyshell__BuiltInCommand__

#include <cstdlib>
#include <string>
#include "Command.h"

using namespace std;

class SystemCommand: public Command {
public:

	SystemCommand(string command);
	~SystemCommand();

	bool execute();

};

#endif /* defined(__toyshell__BuiltInCommand__) */
