#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

std::pair <std::string,int> extract (std::string elementin) {}

// function to convert integer to string
std::string itoa(int a) {
	std::stringstream ss;
	ss<< a;
	return ss.str();
}
// function to reduce ion to aid in reduction of an ion to emperical formula
std::string coeff_H(std::string ionin) {
	std::vector <std::string> stringVec;
	boost::regex ecomatch("[A-Z][a-z]*[0-9]*");
	boost::regex comatch("[0-9]+");
	boost::regex ematch("[A-Z][a-z]*");
	boost::regex mcomatch("[0-9]+$");

	boost::match_results <std::string::const_iterator> match1;
	boost::match_results <std::string::const_iterator> match2;
	boost::match_results <std::string::const_iterator> match3;


	boost::regex_iterator <std::string::iterator> test(ionin.begin(),ionin.end(), ecomatch);
	boost::regex_iterator <std::string::iterator> end;
	std::string returnString = "";
	int mco = 1;

	// match the ion's Coefficient once rather than repeatedly in the while loop
	if(boost::regex_search(ionin, match3, mcomatch)){		
		mco = std::atoi(match3.str().c_str());
	}

	while(!(test==end)) {

		std::string bla(test->str());				// store string that comes in
		boost::regex_search(bla, match1, ematch);		// match an element
		boost::regex_search(bla, match2, comatch);		// match the element's coefficient
		
		// if there is a coefficient perform multiplications 
		// statement is here to prevent error
		if(boost::regex_search(bla, match2, comatch)){
			stringVec.push_back(match1.str().append(itoa(std::atoi(match2.str().c_str())*mco)));
		}else{
			stringVec.push_back(match1.str().append(itoa(mco)));
		}
		++test;
	}
	for(int i = 0; i < stringVec.size(); i++){
		returnString.append(stringVec[i]);
	}
	return returnString;
}
// function to convert a string with brackets to its regex expression
std::string convert(std::string stringin) {
	boost::regex l("\\[");
	boost::regex r("\\]");
	stringin = boost::regex_replace(stringin,l,"\\\\[");
	stringin = boost::regex_replace(stringin,r,"\\\\]");
	return stringin;
}
// function to convert ion to emperical formula
std::string ion_emp(std::string moly) {
	std::vector<std::vector<std::string> > alpha_storage;	// vector to store vector of strings which will hold the empirical ion and the expression to match its position 
	std::vector<std::string> beta_storage;
	boost::regex ionMatch("(\\[[^\\[][^\\]][A-Za-z0-9]*\\][0-9]*)");

	// regex findall instance iterators to find and store ions in the molecule
	boost::regex_iterator <std::string::iterator> test(moly.begin(),moly.end(), ionMatch);
	boost::regex_iterator <std::string::iterator> end;

	// determine what if any ions need to be replaced
	while(!(test == end)) {
		// replace ion
		beta_storage.push_back(coeff_H(test->str()));
		beta_storage.push_back(convert(test->str()));
		alpha_storage.push_back(beta_storage);
		beta_storage.clear();
		++test;
	}
	// replace all the ions with the emperical notation
	for(int i = 0; i<alpha_storage.size(); i++) {
		boost::regex rpMatch(alpha_storage[i][1].c_str());
		moly = boost::regex_replace(moly, rpMatch, alpha_storage[i][0]);
	}
	return moly;
}



std::string Emperical(std::string Molecule) {
	boost::regex ionMatch("\\[|\\]");
	// repeatedly perform operation until there are no brackets left
	do {
		Molecule = ion_emp(Molecule);
	} while(boost::regex_search(Molecule,ionMatch));

	return Molecule;
}
int main() {
	return 0;
}
