//
//  main.cpp
//  toyshell
//
//  Created by Hamad Almarri on 2014-09-06.
//

#include "Shell.h"

using namespace std;

int main(int argc, const char * argv[]) {

	Shell s;
//	s.startShell();

	SystemCommand s1(&s, "ls");
	SystemCommand s2(&s, "ps");
	SystemCommand s3(&s, "cat");

	Jobs jobs;
	jobs.addJob(12341, &s1);
	jobs.addJob(6464, &s2);
	jobs.addJob(124677771, &s3);

	jobs.printJobs();

	return 0;
}

