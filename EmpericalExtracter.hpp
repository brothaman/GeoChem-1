#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <utility>


// function to convert integer to string
std::string itoa(int a) {
	std::stringstream ss;
	ss<< a;
	return ss.str();
}
// function to find all matches in a string
std::vector <std::string> findall(std::string string_in, std::string match) {
	std::vector <std::string> returnVec;
	boost::regex _match(match);

	// iterators to retrieve results from match
	boost::regex_iterator <std::string::iterator> test(string_in.begin(),string_in.end(), _match);
	boost::regex_iterator <std::string::iterator> end;

	while(!(test == end)) {
		returnVec.push_back(test->str());
		++test;
	}
	return returnVec;
}
// EXTRACT
// function that extracts and seperates the atom and its coefficients
std::pair < std::string, int> extract(std::string elementin) {

	std::pair < std::string, int> return_pair;
	boost::regex coeff_match("[0-9]+");
	boost::regex elem_match("[A-Z][a-z]*");

	boost::match_results <std::string::const_iterator> match1;
	boost::match_results <std::string::const_iterator> match2;

	boost::regex_search(elementin, match1, elem_match);
	if(boost::regex_search(elementin, match2, coeff_match)) {
		return_pair = std::make_pair( match1.str(), atoi(match2.str().c_str()));
	}else{
		return_pair = std::make_pair( match1.str(), 1);
	}
	return return_pair;
}
// function to reduce ion to aid in reduction of an ion to emperical formula
std::string coeff_H(std::string ionin) {
	boost::regex mcomatch("\\][0-9]+$");

	boost::match_results <std::string::const_iterator> match1;
	std::string returnString = "";
	int mco = 1;

	// match the ion's Coefficient once rather than repeatedly in the while loop
	if(boost::regex_search(ionin, match1, mcomatch)){		
		mco = std::atoi(match1.str().replace(0,1,"").c_str());
	}

	std::vector <std::string> vec(findall(ionin, "[A-Z][a-z]*[0-9]*"));
	for(int i = 0; i < vec.size(); i++) {
		returnString.append(extract(vec[i]).first);
		returnString.append(itoa(extract(vec[i]).second*mco));
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
	// findall of the inner ions in the molecule passed in
	std::vector <std::string> vec(findall(moly,"(\\[[^\\[][^\\]][A-Za-z0-9]*\\][0-9]*)"));
	
	for(int i = 0; i < vec.size(); i++) {
		boost::regex rpMatch1(convert(vec[i]).c_str());
		moly = boost::regex_replace(moly, rpMatch1, coeff_H(vec[i]));
	}

//	std::cout << moly << std::endl;
	return moly;
}

// Compress expaded form of molecule to emperical form
std::string Compress(std::string molyin) {
	std::vector <std::string> vec(findall(molyin,"[A-Z][a-z]*[0-9]*"));
	std::vector <std::string> testVec;
	std::string stest;
	std::string instring;
	std::string molyout;


	while(!vec.empty()) {
		//
		int return_coeff = 0;
		instring = extract(vec.back()).first;
		stest = extract(vec.back()).first;
		testVec = findall(molyin, stest.append("[0-9]*"));		// find every occurence of each atom
		for(int j = 0; j < testVec.size(); j++ ) {
			return_coeff = return_coeff + extract(testVec[j]).second;
		}

		if(findall(molyout, instring).empty()) {
			molyout.append(instring.append(itoa(return_coeff)));
		}
		vec.pop_back();
	}

	return molyout;

}	
