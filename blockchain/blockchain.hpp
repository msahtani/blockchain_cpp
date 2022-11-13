#include <iostream>
#include "../block/block.hpp"

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

class Blockchain {
    
    private:
        Block* lastBlock;
        
        void mine(Block*);
        void updateBlock(size_t, const string &,Block*);

    public:
        Blockchain(const string&);
        ~Blockchain();

        Block* getLastBlock();
        size_t size();
        void addBlock(const string&);
        void updateBlock(size_t, const string &);
        friend ostream& operator<<(ostream&, const Blockchain &);
        void mine();
};

#endif