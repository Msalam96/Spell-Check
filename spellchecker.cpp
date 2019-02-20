#include "spellchecker.h"

using namespace std;
//Constructor that takes file name as a paramter and isnerts words from that file to the
//dictionary
SpellChecker::SpellChecker(string fileName) {
	ifstream myFile;
	string word;

	myFile.open(fileName);

	if (myFile.good()) { 
		cout << "-> The dictionary has been read." << endl;
		while(!myFile.eof()) {
			myFile >> word;
			dictionary.insert(word);
		}

		myFile.close();
		flag_ = true;
	} else {
		flag_ = false;
	}
}

void SpellChecker::print() {
	unordered_set<string>::const_iterator it;

	for (it=dictionary.begin(); it!= dictionary.end(); ++it) {
		cout << *it << endl;
	}
}

bool SpellChecker::contains(string word) {
	unordered_set<string>::const_iterator it;

	it = dictionary.find(word);
	if (it == dictionary.end()) {
		return false;
	} else {
		return true;
	}
}

//Actual spellcheck engine that saves all corrected words to a vector
vector<string> SpellChecker::spellcheck(string word) {
	vector<string> vec;
	int len = word.length();
	
	//method 1 : go through the word character by character and erase it
	//this handles words with extra letters such as "dogg"
	for (int i = 0; i < len; ++i) {
		string temp = word;
		temp.erase(i, 1);
		if (contains(temp)) {
			vec.push_back(temp);
		}
	}
	//method 2, swap each character with a neighboring character
	//this words for typos like dgos
	for (int i = 0; i < (len-1); ++i) {
		string temp = word;
		string temp2 = word;

		temp2[0] = temp[i];
		temp[i] = temp[i+1];
		temp[i+1] = temp2[0];

		if (contains(temp)) {
			vec.push_back(temp);		
		}
	}
	//method 3, swap each character into each position to see if a word is formed
	//this is for typos with missing letters like dg
	//97 represents the value for 'a' that the compiler stores a in
	for (int i = 0; i < len; ++i) {
		for (int j=97; j<122; ++j) {
			string temp = word;
			char x = (char)(j);
			string y(1,x);
			temp.insert(i,y);
			if (contains(temp)) {
				vec.push_back(temp);			
			}
		}
	}
	//method 4, replace each letter with each letter from the alphabet
	//this is for typos like xog
	for (int i = 0; i < len; ++i) {
		for (int j = 97; j < 122; ++j) {
			string temp = word;
			char x = (char)(j);
			temp[i] = (char)x;
			if (contains(temp)) {
				vec.push_back(temp);
			}
		}
	}
	return vec;
}


