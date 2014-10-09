//
//  Alias.h
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#ifndef __toyshell__Alias__
#define __toyshell__Alias__

#include <iostream>
#include <string>
#include "Command.h"
#include "SystemCommand.h"

using namespace std;

class Alias: public Command {
public:

	Alias(string alias, string commandStr);
	~Alias();

	bool execute();

	string getAliasString() const;

	bool operator!=(const Alias &rhs);

private:
	string alias;
	Command *command;
};

#endif /* defined(__toyshell__Alias__) */
