//
//  OneLine.cpp
//  toyshell
//
//  Created by Hamad Almarri
//

#include "oneline.h"

OneLine::OneLine(string delim) {
	this->delim = strdup(delim.c_str());
	this->wordCount = 0;
	this->oneLine = "";
	this->words = NULL;
}

OneLine::~OneLine() {
	//Clean up the array of words
	this->resetLine();
	free(this->delim);
}

void OneLine::breakLine() {

//	char delim[] = " ";
	char *token;
	unsigned i = 0;
	this->wordCount = 0;

	// create temporary c String version of oneLine
	char *copyOfOneLine = strdup(this->oneLine.c_str());

	/********* count how many words **********/
	token = strtok(copyOfOneLine, delim);

	if (token == NULL)
		this->wordCount = 0;
	else
		this->wordCount++;

	while ((token = strtok(NULL, delim)) != NULL)
		this->wordCount++;


	// if no words at all just return empty string
	if (this->wordCount == 0) {
		this->words = new string[1];
		this->words[0] = "";
		return;
	}

	/********** break the line **********/
	free(copyOfOneLine);
	copyOfOneLine = strdup(this->oneLine.c_str());

	this->words = new string[this->wordCount];
	token = strtok(copyOfOneLine, delim);

	this->words[0] = string(token);

	while (((token = strtok(NULL, delim)) != NULL) && ++i)
		this->words[i] = string(token);

	free(copyOfOneLine);
	free(token);
}

istream& OneLine::readLine(istream& is) {
	resetLine();
	getline(is, this->oneLine);
	breakLine();
	return is;
}

void OneLine::setOneLine(string oneline) {
	this->oneLine = oneline;
	breakLine();
}

string* OneLine::getWords(int &wordCount) {
	wordCount = this->wordCount;
	return this->words;
}

string OneLine::getFirstWord() {
	return this->words[0];
}

string OneLine::returnLine() {
	return this->oneLine;
}

void OneLine::resetLine() {

	//Clean up the array of words
	if (this->words)
		delete[] words;

	this->oneLine = "";
	this->wordCount = 0;
}
