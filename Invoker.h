//
//	Invoker is a class that is responsible for
//	adding/removing/executing commands objects
//	commands are added in queue
//
//	created by Hamad Almarri
//

#ifndef __toyshell__Invoker__
#define __toyshell__Invoker__

#include <iostream>
#include "Command.h"
#include <deque>

using namespace std;

class Invoker {
public:

	/*
	 constructor
	 */
	Invoker();

	/*
	 deconstructor
	 */
	~Invoker();

	/*
	 adding a command to the queue
	 */
	void addCommand(Command *cmd);

	/*
	 Adding a command to the queue and execute.
	 */
	bool addAndExecuteCommand(Command *cmd);

	/*
	 execute a command
	 
	 return:	if executing a command is failed,
	 	 then returns false
	 */
	bool execute(Command *cmd);

	/*
	 * execute a commad that already placed in the queue
	 */
	bool execute(unsigned int at);

	/*
	 * get a specific command by position
	 */
	Command* getCommand(unsigned int at);

	/*
	 * print all commands
	 */
	void printHistory();

private:
	std::deque <Command*> commands;
	static unsigned int maxHistory;
};

#endif
