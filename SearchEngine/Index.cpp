#include "Index.h"
#include <unordered_map>

void Index::makeIndex(AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &wordTree, unordered_map<string, shared_ptr<Doc>> &peopleMap, unordered_map<string, shared_ptr<Doc>> &orgsMap)
{
    ofstream output;
    output.open("index.csv");
    for (auto w : wordTree.getKeys())
    {
        output << w << endl; // write word to file
        for (auto x : wordTree.getValues(w))
        {
            // write info of document to file
            output << x.second << endl;
            output << x.first->uuid << endl;
            output << x.first->title << endl;
            output << x.first->author << endl;
            output << x.first->published << endl;
            output << x.first->text << endl;
            output << "END OF TEXT" << endl;
        }
        output << "NEXT WORD" << endl;
    }
    output.close();

    // persistence of persons
    output.open("people.csv");
    for (auto p : peopleMap)
    {
        output << p.first << endl;
        output << p.second->uuid << endl;
        output << p.second->title << endl;
        output << p.second->author << endl;
        output << p.second->published << endl;
        output << p.second->text << endl;
        output << "END OF TEXT" << endl;
        output << "NEXT PERSON" << endl;
    }
    output.close();

    // persistence of orgs
    output.open("orgs.csv");
    for (auto o : orgsMap)
    {
        output << o.first << endl;
        output << o.second->uuid << endl;
        output << o.second->title << endl;
        output << o.second->author << endl;
        output << o.second->published << endl;
        output << o.second->text << endl;
        output << "END OF TEXT" << endl;
        output << "NEXT ORG" << endl;
    }
    output.close();
}

void Index::readIndex(AvlTree<string, unordered_map<shared_ptr<Doc>, int, HashFunction>> &tree)
{
    ifstream input;
    input.open("index.csv");
    if (!input.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }

    string word, id, title, author, published, text, num, line;
    getline(input, word);
    while (!input.eof()) // reading info from file to add to tree
    {
        tree.insert(word);
        getline(input, num);
        do
        {
            getline(input, id);
            getline(input, title);
            getline(input, author);
            getline(input, published);
            getline(input, line);
            do
            {
                line.append("\n");
                text.append(line);
                getline(input, line);
            } while (line != "END OF TEXT");
            shared_ptr<Doc> d(new Doc(title, id, published, author, text));
            text.clear();
            tree[word][d] = stoi(num);
            getline(input, num);
        } while (num != "NEXT WORD");
        getline(input, word);
    }
}

void Index::readPerson(unordered_map<string, shared_ptr<Doc>> &peopleMap)
{
    ifstream input;
    input.open("people.csv");
    if (!input.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }
    string name, id, title, author, published, text, line;
    getline(input, name);
    while (!input.eof()) // reading info from file to add to tree
    {
        peopleMap[name];
        getline(input, id);
        do
        {
            getline(input, title);
            getline(input, author);
            getline(input, published);
            getline(input, line);
            do
            {
                line.append("\n");
                text.append(line);
                getline(input, line);
            } while (line != "END OF TEXT");
            shared_ptr<Doc> d(new Doc(title, id, published, author, text));
            peopleMap[name] = d;
            getline(input, id);
        } while (id != "NEXT PERSON");
        getline(input, name);
    }
}

void Index::readOrg(unordered_map<string, shared_ptr<Doc>> &orgMap)
{
    ifstream input;
    input.open("orgs.csv");
    if (!input.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }
    string name, id, title, author, published, text, line;
    getline(input, name);
    while (!input.eof()) // reading info from file to add to tree
    {
        orgMap[name];
        getline(input, id);
        do
        {
            getline(input, title);
            getline(input, author);
            getline(input, published);
            getline(input, line);
            do
            {
                line.append("\n");
                text.append(line);
                getline(input, line);
            } while (line != "END OF TEXT");
            shared_ptr<Doc> d(new Doc(title, id, published, author, text));
            orgMap[name] = d;
            getline(input, id);
        } while (id != "NEXT ORG");
        getline(input, name);
    }
}