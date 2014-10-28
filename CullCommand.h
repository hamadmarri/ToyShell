/*
 * CullCommand.h
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#ifndef CULLCOMMAND_H_
#define CULLCOMMAND_H_

#include <string>
#include "ShellCommand.h"
#include "SystemCommand.h"

class ShellCommand;

using namespace std;

class CullCommand: public ShellCommand {
public:
	CullCommand(Shell *shell, string *parts, int wordCount);
	bool execute();
};

#endif /* CULLCOMMAND_H_ */
