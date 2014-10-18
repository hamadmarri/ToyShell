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

	for (it = jobs.begin(); it < jobs.end(); it++, i++) {
		updateStatus(it);

		cout << '[' << i << ']' << '\t' << it->status << '\t'
				<< it->command->getCommandString() << '\t' << it->pid << '\t'
				<< formatTime(it) << endl;

		if (it->status == "completed")
			jobs.erase(it);
	}
}

string Jobs::formatTime(vector<Job>::iterator it) {
	// to get time as string
	char timeAsString[80];
	struct tm * timeinfo;

	// format time
	timeinfo = localtime(&it->createdTime);
	strftime(timeAsString, 80, "%c.", timeinfo);

	return timeAsString;
}

void Jobs::updateStatus(vector<Job>::iterator it) {
	int status;
	int waitReturn;

	waitReturn = waitpid(it->pid, &status, WNOHANG);
	if (waitReturn != 0 && WIFEXITED(status))
		it->status = "completed";
}

void Jobs::waitForJob(unsigned int i) {
	int status;
	string commandString;

	if (i < 1 || i > jobs.size()) {
		cout << "There is no job with id: " << i << endl;
		return;
	}

	commandString = jobs.at(i - 1).command->getCommandString();

	cout << commandString.substr(0, commandString.size() - 2) << endl;

	waitpid(jobs.at(i - 1).pid, &status, WUNTRACED);

	jobs.erase(jobs.begin() + i - 1);
}

void Jobs::waitForAllJobs() {
	int status;
	int pid;
	while ((pid = wait(&status)) != -1)
		cout << "job with pid = " << pid << " has been completed" << endl;
}

