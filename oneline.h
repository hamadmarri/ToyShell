//
//  OneLine.h
//  toyshell
//
//  Created by Hamad Almarri
//

#ifndef __toyshell__OneLine__
#define __toyshell__OneLine__

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class OneLine {
public:
	OneLine(string delim);
	~OneLine();
	void breakLine();
	istream &readLine(istream& is);
	string returnLine();
	string* getWords(int &wordCount);
	string getFirstWord();
	void setOneLine(string oneline);

private:
	char *delim;
	string oneLine;
	string *words;
	int wordCount;
	void resetLine();
};

#endif
