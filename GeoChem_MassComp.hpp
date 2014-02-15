// 
// Program Atom!
// Programmer Robert Brothers Student Engineer and Chemist at UTSA 
// Contact @ rbrothers12@gmail.com
// Full Resume is avalable on LinkedIn social network
//
//




#include <iostream>
#include <math.h>
#include <boost/regex.hpp>
#include <vector>
#include <utility>
#include <map>


// molecule is made of 2 or more atoms
class Molecule {
	public:
		std::string Molecule;
		// accept a molecue in its emperical formula and calculate its formula mass
		double FormulaMass () {
			std::string moly(EmpericalReduction(Molecule));
			boost::regex Ematch("[A-Z][a-z]*[0-9]*");		// atoms and their quatities
			
			// Vector to store the elements in the emperical formula
			std::vector <std::pair <std::string, int> > alpha_storage;

			// find all of the elements in the molecule
			boost::regex_iterator <std::string::iterator> matches ( moly.begin(), moly.end(), Ematch);
			boost::regex_iterator <std::string::iterator> end;

			while(!(matches == end)){
				// store the pairs in vector
				alpha_storage.push_back(std::make_pair(extract(matches->str()).first, extract(matches->str()).second));
				++matches;
			}
			double MolarMass = 0;

			for(int i =0; i<alpha_storage.size() ; i++) {
				MolarMass = MolarMass + atomic_data.find(alpha_storage[i].first)->second.second * alpha_storage[i].second;
			}
			return MolarMass;
		}
		std::string MolecularGeometry() {
			std::vector <std::string> atoms(findall(Molecule, "[A-Z][a-z]*[0-9]*"));
			int no_atoms = 0;
			for(int i = 0; i<atoms.size(); i++){
//				no_atoms = atoi(extract(atoms[i]*1)) + no_atoms;
			}
			if(atoms.size() > 5) {
				
			}
		}
	private:
		// i.e. Fe[CN]2[OH2]2 to Fe1C2N2O2H4
		std::string EmpericalReduction (std::string Molecule) {
			// data comes in as K2[Cr2O7]2[CH3COO]2 and possible Fe[CO2[P[O2]2]3]4
			boost::regex ionMatch("\\[|\\]");
			// repeatedly perform operation until there are no brackets left
			do {
				Molecule = ion_emp(Molecule);
			} while(boost::regex_search(Molecule,ionMatch));
			return Compress(Molecule);
		}
		int no_atoms(std::string ion) {
			std::vector <std::string> atoms(findall(Molecule, "[A-Z][a-z]*[0-9]*"));
			int number_of_atoms = 0;
			for( int i = 0; i < atoms.size(); i++) {
				number_of_atoms = number_of_atoms + extract(atoms[i]).second*1;
			}
			std::cout << number_of_atoms << std::endl;
			return number_of_atoms;
		}
		std::pair <std::string, int> valen_vec();

};

