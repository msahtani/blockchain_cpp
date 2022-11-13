#include <iostream>
#include "blockchain/blockchain.hpp"
#include "block/block.hpp"

using std::cout;

int main(int argc, char** argv){
	
	Blockchain b("mohcine");
	b.addBlock("yassine");
	b.addBlock("siham");
	b.addBlock("brahim");
	b.addBlock("saida");

	cout << b;

	cout << "-----------------------------------------\n\n";

	b.mine();
	cout << b;

	return 0;
}

