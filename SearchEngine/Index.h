#ifndef INDEX_H
#define INDEX_H

#include "AvlTree.h"
#include "Parser.h"
#include <fstream>

using namespace std;

class Index
{
public:
    Index(){};
    void makeIndex(AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap);
    void readIndex(AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &tree);
    void readPerson(unordered_map<string, shared_ptr<Doc>> &peopleMap);
    void readOrg(unordered_map<string, shared_ptr<Doc>> &orgsMap);

};

#endif