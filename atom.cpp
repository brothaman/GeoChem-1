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
#include "EmpericalExtracter.hpp"
#include "atom_data.hpp"
#include "GeoChem_ElementFactory.hpp"
#include "GeoChem_MassComp.hpp"


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
