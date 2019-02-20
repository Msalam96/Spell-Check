//Mohammed Salam
#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <string>
#include <unordered_set>
//#include <set>
#include <fstream>
#include <iostream>
#include <vector>

//This is the spellchcker class that stores the dictionary into a unordered_Set
//I am sending the file as a unordered set as that is the faster one, when
//making my experiments i simply made a ordered set dictionary and ran that in main
class SpellChecker {
public:
	SpellChecker(std::string fileName);
	void print();
	bool contains (std::string word);
	std::vector<std::string> spellcheck(std::string word);
	bool flag() {return flag_;};
private:
	std::unordered_set<std::string> dictionary;
	//std::set<std::string> dictionary;
	bool flag_;
};

#endif