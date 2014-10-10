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
}

void Jobs::removeJob(unsigned int i) {

}

void Jobs::printJobs() {
	unsigned int i = 1;
	vector<Job>::iterator it;
	for (it = jobs.begin(); it < jobs.end(); it++, i++) {
		cout << i << '\t' << it->pid << '\t' << it->command->getCommandString() << '\t' << it->createdTime << endl;
	}
}

void Jobs::waitForJob() {

}
