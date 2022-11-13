#include <iostream>
#include <cstring>
#include <chrono>
#include "../sha256/sha256.hpp"
#include "block.hpp"

using namespace std::chrono;
using namespace std;

size_t getCurrentTimestamp(){
	return duration_cast<milliseconds>(
		system_clock::now()
		.time_since_epoch()
	).count();
}

string Block::toString() const {

	return to_string(id) + " " 
		+ data + " "
		+ to_string(nonce) + " "
		+ (prev_block ? prev_block->hash : ZERO_HASH);
}

string Block::getHash(){
	string text = toString();
	SHA256 sha;
	sha.add(text.data(), text.size());
	return sha.getHash();
}

void Block::updateHash(){
	hash = getHash();
	timestamp = getCurrentTimestamp();
}

Block::Block(string _data): id(1){
	data = _data;
	prev_block = NULL;

	updateHash();
}

Block::Block(string _data, Block *prev):
 	id(prev->id + 1){
	prev_block = prev;
	data = _data;
	updateHash();
}

ostream& operator<<(ostream &out, const Block &b){

	out << "id: "   	 << b.id        << "\n"
		<< "data: " 	 << b.data      << "\n"
		<< "nonce:" 	 << b.nonce     << "\n"
		<< "timestamp: " << b.timestamp << "\n"
		<< "hash: "      << b.hash      << "\n"
		<< "prev hash: " << (b.prev_block ? b.prev_block->hash : ZERO_HASH) 
		<< "\n\n";
	return out;
}

bool Block::mined(){
	return hash.substr(0,4) == "0000";
}

void Block::mine(){
	nonce = 0;
	while(!mined()){
		nonce++;
		updateHash();
	}
	timestamp = getCurrentTimestamp();
}

void Block::modifyData(string _data){
	data = _data;
	updateHash();
}

Block* Block::getPrevBlock(){
	return prev_block;
}