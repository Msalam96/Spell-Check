#include "spellchecker.h"
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <locale>
using namespace std::chrono;

//Token struct to be used as delimeters. This is to break down whole sentences read from
//check_it.txt and gather each word and read it into a vector.
struct tokens: std::ctype<char> {
	static const mask* make_table() {
		static std::vector<mask> v(classic_table(), classic_table() + table_size);
		v[','] |=  space;
		v[' '] |=  space;
		v['.'] |=  space;
		v['-'] |=  space;
		v['\''] |=  space;
		return &v[0];
	}
	tokens(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};

int main(int argc, char* argv[]) {
	if (argc > 3 || argc < 3) {
		std::cerr << "-> Please run again with only 2 filenames." << std::endl;
		return 0;
	} else {
		SpellChecker checker(argv[2]);
		if (checker.flag() == false) {
			std::cerr << "-> The dictionary file was not found, please try again." << std::endl;
			return 0;
		} else {
		//checker.print();
			//checker.print();
			std::vector<std::string> text;

			std::ifstream myFile;
			std::string word;

			myFile.open(argv[1]);
			if (myFile.good()) {
				std::cout << "-> The file to be checked has been read." << std::endl;
				while(getline(myFile, word)) {
					text.push_back(word);
				}

				myFile.close();

				
				std::vector<std::string> check_it;

				//tolower the words in the vector, parse through to find tokens, push into vectors
				for (unsigned int i = 0; i < text.size(); ++i) {
			        std::string data = text[i];
			        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
			        std::stringstream ss(data);
			        ss.imbue(std::locale(std::locale(), new tokens()));
			        std::istream_iterator<std::string> begin(ss);
			        std::istream_iterator<std::string> end;
			        std::vector<std::string> vstrings(begin, end);
			        std::copy(vstrings.begin(), vstrings.end(), std::back_inserter(check_it));
			        //std::transform(vstrings.begin(), vstrings.end(), vstrings.begin(), ::tolower);
			        //check_it2.push_back(vstrings[i]);
			    }


			    std::vector<std::string> corrections;

			    std::ofstream of;
			    std::string out;
			    std::cout << "-> Input a file to save your corrections to: ";
			    std::cin >> out;
			    of.open(out);

			    std::ofstream time;
			    time.open("unordered_set_time.txt");
			    auto start = high_resolution_clock::now();
			    //run the check
			    for (int i = 0; i < check_it.size(); i++) { 
			    	if (checker.contains(check_it[i]) == false && check_it[i].size() > 1) {
			    		of << check_it[i] << " was not found. Did you mean: " << std::endl;
			    		corrections = checker.spellcheck(check_it[i]);
			    		if (corrections.empty()) {
			    				of << "   -> no suggestions available" << std::endl;
			    		}
			    		for (int i = 0; i < corrections.size(); ++i) {
			    			of << "   -> " << corrections[i] << std::endl;
			    		}
			    		of << std::endl;
			    	}
			    } 
			    auto stop = high_resolution_clock::now(); 
			    auto duration = duration_cast<microseconds>(stop - start); 
			    time << "Spellcheck has taken " << duration.count() << " milliseconds to run." << std::endl;
			    std::cout << "-> The time elasped has been saved to unordered_set_time.txt." << std::endl;
			    time.close();
			    of.close();
			    std::cout << "-> The corrections have been successfully saved to " << out << "." << std::endl;
			} else {
				std::cerr << "-> The file to be checked was not found, please try again." << std::endl;
				return 0;
			}
		}
	}
      
}