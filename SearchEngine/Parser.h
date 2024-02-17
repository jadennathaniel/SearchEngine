#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "AvlTree.h"
#include <unordered_map>

// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "Doc.h"
#include "HashFunction.h"
#include "porter2_stemmer.h"

using namespace std;
using namespace rapidjson;

class Parser
{

private:
    int numDocs;
public:
    Parser(){};
    void readJsonFile(const string &path, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap, AvlTree<string, string> &);
    void fileSystem(const string &path, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap, AvlTree<string, string> &);
    void addToTree(const string &text, shared_ptr<Doc> document, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, AvlTree<string, string> &);
    AvlTree<string, string> &readStopWords(AvlTree<string, string> &);
    void setNumDocs(int i)
    {
        numDocs = i;
    }
    int getNumDocs()
    {
        return numDocs;
    };
};

#endif