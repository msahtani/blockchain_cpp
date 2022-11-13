#include <iostream>
#include <cstring>

#ifndef BLOCK_H
#define BLOCK_H

using std::string;
using std::ostream;

const string ZERO_HASH = "0000000000000000000000000000000000000000000000000000000000000000";

size_t getCurrentTimestamp();


class Block{

    private:
		string data;
		size_t timestamp;
		size_t nonce;
		string hash;
		Block *prev_block;

        string toString() const;


    public:
        // public read-only attribute (id)
        const size_t id;
        // constructors
        Block(string);
        Block(string, Block *);

        friend ostream& operator<<(ostream&, const Block &);
        bool mined();
        void mine();
        void modifyData(string);
        string getHash();
        void updateHash();
        Block* getPrevBlock();
};

#endif