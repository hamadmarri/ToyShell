/*
 * UsescriptCommand.h
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#ifndef USESCRIPTCOMMAND_H_
#define USESCRIPTCOMMAND_H_

#include <string>
#include <fstream>
#include "ShellCommand.h"
#include "SystemCommand.h"

class ShellCommand;

using namespace std;


class UsescriptCommand: public ShellCommand {
public:
	UsescriptCommand(Shell *shell, string *parts, int wordCount);
	bool execute();

private:
	bool executeCommand(OneLine &ol);
	bool isExceedLimit(Command *cmd);

	unsigned int fileRecursionLimit;

};

#endif /* USESCRIPTCOMMAND_H_ */
