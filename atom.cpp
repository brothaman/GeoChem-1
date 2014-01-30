// 
// Program Atom!
// Programmer Robert Brothers Student Engineer at UTSA 
// Contact @ rbrothers12@gmail.com
//




#include <iostream>
#include <math.h>
#include <boost/regex.hpp>
#include <vector>
#include <utility>
#include <map>
#include "EmpericalExtracter.hpp"
#include "atom_data.hpp"

long double Mele = 9.10938291*pow(10,-28);
long double Mneu = 1.674927351*pow(10,-24);
long double Mpro = 1.67262178*pow(10,-24);
long double avN = 6.02214108979663699470280*pow(10,23);

// no need to define atomic mass this is calculated for each atom and isotope
class Element {
	public:
		std::string element;
		long double MolarMass(int protons, int neutrons){
			return avN*(protons*Mele + protons*Mpro + neutrons*Mneu);
		}
		int bondingElectrons() {
			int electrons = atomic_data[element].first;
			int vElectrons = valenceElectrons(electrons);
			std::cout << vElectrons << std::endl;
			if(vElectrons < 2) {
				if(vElectrons == 1) {
					return 1;
				}else {
					return 0;
				}
			}else if(!vElectrons/4){
				std::cout << "here line 36" << std::endl;
				return vElectrons%4; 
			}else{
				return 4-vElectrons%4;
			}
		}
		int pairingElectrons() { 
			int electrons = atomic_data[element].first;
			int vElectrons = valenceElectrons(electrons); 
			return (vElectrons%4)*2; 
		}
	private:
		int valenceElectrons(int electrons){
			int eleft(electrons),valence = 0,n=0;
			while(eleft >= 0) {
				valence = eleft;
				if(n==1){
					eleft = eleft-2;
				}
				else if(n <= 3 && n > 1){
					eleft = eleft - 8;
				}
				else if(n <= 5 && n > 3){
					if(valence > 2){
						valence = valence - 10;
					}
					eleft = eleft - 18;
				}
				else if(n > 5){
					if(valence > 2){
						valence = valence - 24;
					}
					eleft = eleft-32;
				}
				n++;
			}
			std::cout << "Number of Valence Electrons: " << valence << std::endl;
			return valence;
		}
		std::string ElectronConfiguration(int electrons){
			
		}

};

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
// an algorithm that cycles through the valence electrons and determines bonding and non-bonding electrons
// -> it needs to cycle through and distribute electrons in shell so that spins are opposites 
// A class molecule needs to contain capability of defining central atom and hybridization of central atom



int main(){
	Element atom;
	atom.element = "H";
	a_data();
	std::cout << "Oxygen has " << atom.bondingElectrons() << " bonding Electron(s), " << atom.pairingElectrons() << " and pairing Electron(s). " << std::endl;
	Element some;
//	std::cout << some.MolarMass(8,8) << std::endl;
	Molecule bla;
	bla.Molecule = "H2O";
//	std::cout << ion_emp("[Fe2B4H4]3") << std::endl;
//	std::cout << "Number of Pairing Electrons: " << pairing << std::endl;
	std::cout << bla.FormulaMass() << std::endl;
	return 0;
}
