/*
 * ExclamationCommand.h
 *
 *  Created on: 2014-10-14
 *      Author: hamadmarri
 */

#ifndef EXCLAMATIONCOMMAND_H_
#define EXCLAMATIONCOMMAND_H_

#include <string>
#include <sstream>
#include "ShellCommand.h"

class ShellCommand;

using namespace std;


class ExclamationCommand : public ShellCommand {
public:

	ExclamationCommand(Shell *shell, string *parts, int wordCount);
	bool execute();

};

#endif /* EXCLAMATIONCOMMAND_H_ */
