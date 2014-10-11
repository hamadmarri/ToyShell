/*
 * Job.cpp
 *
 *  Created on: 2014-10-10
 *      Author: hamadmarri
 */

#include "Jobs.h"

Jobs::Jobs() {
	// TODO Auto-generated constructor stub

}

Jobs::~Jobs() {
	// TODO Auto-generated destructor stub
}

void Jobs::addJob(int pid, Command *command) {
	Job j(pid, command);
	this->jobs.push_back(j);
	cout << '[' << this->jobs.size() << "] " << pid << endl;
}

void Jobs::removeJob(unsigned int i) {
	this->jobs.erase(jobs.begin() + i);
}

void Jobs::printJobs() {
	unsigned int i = 1;
	vector<Job>::iterator it;

	// to get time as string
	char timeAsString[80];
	struct tm * timeinfo;

	for (it = jobs.begin(); it < jobs.end(); it++, i++) {
		// format time first

		timeinfo = localtime(&it->createdTime);

		strftime(timeAsString, 80, "%c.", timeinfo);
		//puts(timeAsString);

		cout << '[' << i << ']' << '\t' << it->status << '\t'
				<< it->command->getCommandString() << '\t' << it->pid << '\t'
				<< timeAsString << endl;
	}
}

void Jobs::waitForJob() {

}
