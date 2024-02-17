#include "Query.h"

void Query::parseQuery(const string &words, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &people, unordered_map<string, shared_ptr<Doc>> &orgs, AvlTree<string, string> &stopWordTree, vector<pair<shared_ptr<Doc>, int>> &finalDocs)
{
    stringstream stream(words);
    string word;
    string personCommand = "PERSON:";
    string orgCommand = "ORG";
    vector<string> queryWords;
    while (stream >> word)
    {
        queryWords.emplace_back(word); //put each word from the query into a vector
    }

    unordered_map<shared_ptr<Doc>, int, HashFunction> resultsMap;
    unordered_map<shared_ptr<Doc>, int, HashFunction> notDocs; // documents we don't want
    vector<shared_ptr<Doc>> personOrgVector;
    for (auto &w : queryWords)
    {
        if (stopWordTree.contains(w)) //if query word contains stopword ignore it
            continue;

        if (w.find(personCommand) != string::npos) //if there is a PERSON:
        {
            w.erase(0, personCommand.length()); // removes PERSON: from the word
            searchPerson(w, people, personOrgVector);
            continue;
        }
        else if (word.find(orgCommand) != string::npos) //if there is a ORG:
        {
            w.erase(0, orgCommand.length()); // removes ORG:: from the word
            searchOrg(w, orgs, personOrgVector);
            continue;
        }
        if (w.at(0) == '-') //if there is a -
        {
            w.erase(0, 1);
            Porter2Stemmer::stem(w);
            Porter2Stemmer::trim(w);
            searchNotDocs(w, wordTree, notDocs);
            // find documents that don't contain that word
            // searchIndex(word, wordTree);
        }
        else
        {
            Porter2Stemmer::stem(w);
            Porter2Stemmer::trim(w);
            searchIndex(w, wordTree, resultsMap); // add document vectors to result vector
        }
    }
    if (!notDocs.empty())
    {
        removeNotDocs(resultsMap, notDocs);
    }
    if (!personOrgVector.empty())
    {
        finalDocs = joinSets(personOrgVector, resultsMap);
    }
    else
    {
        for (auto &d : resultsMap)
        {
            finalDocs.emplace_back(d);
        }
    }
}

void Query::searchIndex(const string &word, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<shared_ptr<Doc>, int, HashFunction> &resultsMap)
{
    if (wordTree.contains(word))
    {
        resultsMap.insert(wordTree.getValues(word).begin(), wordTree.getValues(word).end());
    }
    else
    {
        cout << "No results found" << endl;
    }
}

void Query::searchPerson(const string &word, unordered_map<string, shared_ptr<Doc>> &people, vector<shared_ptr<Doc>> &personOrgVector)
{
    for (auto &p : people)
    {
        size_t found = p.first.find(word); // if map contains the name
        if (found != string::npos)
        {
            personOrgVector.emplace_back(p.second); // add the document to vector
        }
    }
}

void Query::searchOrg(const string &word, unordered_map<string, shared_ptr<Doc>> &orgs, vector<shared_ptr<Doc>> &personOrgVector)
{
    for (auto &o : orgs)
    {
        size_t found = o.first.find(word); // if map contains the org
        if (found != string::npos)
        {
            personOrgVector.emplace_back(o.second); // add the document to vector
        }
    }
}

vector<pair<shared_ptr<Doc>, int>> Query::joinSets(vector<shared_ptr<Doc>> &personOrgVector, unordered_map<shared_ptr<Doc>, int, HashFunction> &resultsMap)
{
    vector<pair<shared_ptr<Doc>, int>> resultVector;
    for (auto &v : personOrgVector) 
    {
        if (resultsMap.find(v) != resultsMap.end()) //if the document in personOrgVector exists in resultsMap, add the document to the resultVector
        {
            pair<shared_ptr<Doc>, int> pair;
            pair = std::make_pair(v, resultsMap.at(v));
            resultVector.emplace_back(pair);
        }
    }
    return resultVector;
}

void Query::searchNotDocs(const string &word, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<shared_ptr<Doc>, int, HashFunction> &notDocs)
{
    if (wordTree.contains(word))
    {
        notDocs.insert(wordTree.getValues(word).begin(), wordTree.getValues(word).end());
    };
}

void Query::removeNotDocs(unordered_map<shared_ptr<Doc>, int, HashFunction> &resultsMap, unordered_map<shared_ptr<Doc>, int, HashFunction> &notDocs)
{
    for (auto &v : notDocs)
    {
        if (resultsMap.find(v.first) != resultsMap.end()) //if document in not docs exists in resultsMap, remove the document from the resultsMap
        {
            resultsMap.erase(v.first);
        }
    }
}
