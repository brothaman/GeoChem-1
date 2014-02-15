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


