/*
 * Display.h
 *
 *  Created on: 2014-10-27
 *      Author: hamadmarri
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ShellCommand.h"
#include "SystemCommand.h"

class ShellCommand;

using namespace std;

class DisplayCommand: public ShellCommand {
public:
	DisplayCommand(Shell *shell, string *parts, int wordCount);
	bool execute();
};

#endif /* DISPLAY_H_ */
