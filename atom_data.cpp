#include <map>
#include <iostream>
#include <utility>

int main() {
	std::map < std::string, std::pair< int, int> > atomic_data;
	std::pair <int,int> bla;
	bla = std::make_pair(1,0);
	atomic_data["H"] = std::make_pair(1,0);
	return 0;
}
