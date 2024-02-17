#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "AvlTree.h"
#include "Parser.h"
#include "Index.h"
#include "Query.h"
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;
class UserInterface
{
private:
public:
    AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> wordTree;
    unordered_map<string, shared_ptr<Doc>> people;
    unordered_map<string, shared_ptr<Doc>> orgs;
    AvlTree<string, string> stopWords;
    vector<pair<shared_ptr<Doc>, int>> finalDocs;
    chrono::microseconds time;
    int numDocs;
    void displayMenu();
    void createIndex();
    void writeIndex(); // tree to file
    void readIndex();  // file to tree
    void enterQuery();
    void outputStatistics();
    //void progressbar();
    void relevancyRanking(vector<pair<shared_ptr<Doc>, int>> &finalDocs);
};

#endif