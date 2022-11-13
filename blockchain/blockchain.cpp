#include <iostream>
#include "../block/block.hpp"
#include "blockchain.hpp"

using std::cout;

Blockchain::Blockchain(const string &_data){
    Block* genesis = new Block(_data);
    lastBlock = genesis;
}

Blockchain::~Blockchain(){
    Block* current = lastBlock;
    Block* toDelete = lastBlock;
    while(toDelete){
        current = current->getPrevBlock();
        delete toDelete;
        toDelete = current;
    }
}

size_t Blockchain::size(){
    return lastBlock->id;
}

void Blockchain::addBlock(const string& _data){
    Block* newBlock = new Block(_data, lastBlock);
    lastBlock = newBlock;
}

void Blockchain::updateBlock(size_t id, const string &_data){
    
    if(id == 0 || id > size()){
        cout << "index out of range\n";
        exit(-1);
    }
    updateBlock(id, _data, lastBlock);
}

void Blockchain::updateBlock(size_t id, const string &_data, Block* curr){

    if(curr->id == id){
        curr->modifyData(_data);
        return;
    }

    updateBlock(id, _data, curr->getPrevBlock());
    curr->updateHash();
}

ostream& operator<<(ostream& out, const Blockchain &b){
    Block* curr = b.lastBlock;
    while(curr){
        out << *curr;
        curr = curr->getPrevBlock();
    }

    return out;
}

void Blockchain::mine(){
    mine(lastBlock);
}

void Blockchain::mine(Block* current) {
    
    if(current->mined()) return;

    if(current->id != 1)
        mine(current->getPrevBlock());

    current->mine();
}

