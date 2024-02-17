//taken from https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-user-defined-class-in-cpp/
#ifndef HASHFUNCTION_H
#define HASFUNCTION_H

#include "Doc.h"

//hash function that uses article uuid as hash function
class HashFunction
{
    public:
        size_t operator ()(const shared_ptr<Doc> &d)const
        {
            hash<string> uuidHash;
            return uuidHash(d.get()->uuid);
        }
};

#endif