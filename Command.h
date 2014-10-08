//
//	Command is abstract class or interface that used for command pattern
//	the main functionallity is execute(), which is need to be implemented
//	by concrete classes
//

#ifndef __toyshell__Command__
#define __toyshell__Command__

#include <string>

class Command {
public:
	virtual ~Command(){};
	virtual bool execute() = 0;
	virtual std::string getCommandString() = 0;
};

#endif
