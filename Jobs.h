/*
 * Job.h
 *
 *  Created on: 2014-10-10
 *      Author: hamadmarri
 */

#ifndef JOB_H_
#define JOB_H_

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "Command.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>


using namespace std;

class Job {
public:
	Job(int pid, Command *command) {
		this->pid = pid;
		this->command = command;
		this->createdTime = time(0);
		this->status = "in progress";
	}
	;
	int pid;
	Command *command;
	time_t createdTime;
	string status; // in progress, completed
};

class Jobs {
public:
	Jobs();
	~Jobs();

	void addJob(int pid, Command *command);
	void removeJob(unsigned int i);
	void printJobs();
	void waitForJob(unsigned int i);
	void waitForAllJobs();

private:
	string formatTime(vector<Job>::iterator it);
	void updateStatus(vector<Job>::iterator it);

	vector<Job> jobs;
};

#endif /* JOB_H_ */
