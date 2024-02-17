#include "Parser.h"

void Parser::readJsonFile(const string &path, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap, AvlTree<string, string> &stopWordTree)
{

    ifstream input(path);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << path << endl;
        return;
    }

    readStopWords(stopWordTree);

    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);

    auto val = d["uuid"].GetString();
    auto words = d["text"].GetString();
    auto author = d["author"].GetString();
    auto title = d["title"].GetString();
    auto published = d["published"].GetString();
    shared_ptr<Doc> document(new Doc(title, val, published, author, words));
    addToTree(words, document, wordTree, stopWordTree);

    auto persons = d["entities"]["persons"].GetArray();
    for (auto &p : persons)
    {
        peopleMap[p["name"].GetString()] = document; // put each person into people map
    }

    auto org = d["entities"]["organizations"].GetArray();
    for (auto &o : org)
    {
        orgsMap[o["name"].GetString()] = document; // put each organization into orgs map
    }

    input.close();
    // wordTree.prettyPrintTree();
}

void Parser::fileSystem(const string &path, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap, AvlTree<string, string> &stopWordTree)
{

    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);
    long long counter = 0;
    // loop over all the entries.
    for (const auto &entry : it)
    {
        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            readJsonFile(entry.path().string(), wordTree, peopleMap, orgsMap, stopWordTree);
            counter++;
            if (counter % 10000 == 0)
            {
                cout << counter << " files read" << endl;
            }
        }
    }
    cout << counter << " files read" << endl;
    setNumDocs(counter);
}

void Parser::addToTree(const string &text, shared_ptr<Doc> document, AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, AvlTree<string, string> &stopWordTree)
{
    stringstream inSS(text);
    string word;
    while (inSS >> word)
    {
        if (stopWordTree.contains(word))
        {
            continue;
        }
        Porter2Stemmer::stem(word);
        Porter2Stemmer::trim(word);
        if (!wordTree.contains(word)) // if word is not found in the tree
        {
            wordTree.insert(word);
            wordTree[word][document] = 1;
        }
        else
        {
            wordTree[word][document]++; // if word is already in tree, increment count
        }
    }
}

AvlTree<string, string> &Parser::readStopWords(AvlTree<string, string> &stopWordTree)
{
    ifstream input;
    input.open("words.csv");
    if (!input.is_open())
    {
        throw runtime_error("Could not open file");
    }
    string word;
    while (input >> word)
    {
        stopWordTree.insert(word);
    }
    return stopWordTree;
}