#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <sstream>
#include "AvlTree.h"
#include "Doc.h"
#include "porter2_stemmer.h"
#include <unordered_map>
#include "Parser.h"
using namespace std;

class Query
{
public:
    void parseQuery(const string &words, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &people, unordered_map<string, shared_ptr<Doc>> &orgs, AvlTree<string, string> &, vector<pair<shared_ptr<Doc>, int>> &finalDocs);
    void searchIndex(const string &word, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<shared_ptr<Doc>, int, HashFunction> &resultsMap);
    static bool cmp(pair<shared_ptr<Doc>, int> &a, pair<shared_ptr<Doc>, int> &b);
    void searchPerson(const string &word, unordered_map<string, shared_ptr<Doc>> &people, vector<shared_ptr<Doc>> &);
    void searchOrg(const string &word, unordered_map<string, shared_ptr<Doc>> &orgs, vector<shared_ptr<Doc>> &);
    vector<pair<shared_ptr<Doc>, int>> joinSets(vector<shared_ptr<Doc>> &, unordered_map<shared_ptr<Doc>, int, HashFunction> &);
    void searchNotDocs(const string &word, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<shared_ptr<Doc>, int, HashFunction> &notDocs);
    void removeNotDocs(unordered_map<shared_ptr<Doc>, int, HashFunction> &resultsMap, unordered_map<shared_ptr<Doc>, int, HashFunction> &notDocs);
};

#endif