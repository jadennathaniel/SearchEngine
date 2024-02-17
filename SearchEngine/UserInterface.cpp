#include "UserInterface.h"

using namespace std;

void UserInterface::displayMenu()
{
    while (true)
    {
        cout << "Welcome to Super Search!" << endl;
        cout << "Enter 1 to create index from documents" << endl;
        cout << "Enter 2 to write the index to a file" << endl;
        cout << "Enter 3 to read an index from a file" << endl;
        cout << "Enter 4 to enter a query" << endl;
        cout << "Enter 5 to output statistics" << endl;
        cout << "Ener 0 to exit" << endl;

        string answer;
        cin >> answer;
        int answerInt = stoi(answer);
        switch (answerInt)
        {
        case 1:
            createIndex();
            break;
        case 2:
            writeIndex();
            break;
        case 3:
            readIndex();
            break;
        case 4:
            enterQuery();
            break;
        case 5:
            outputStatistics();
            break;
        case 0:
            return;
        default:
            cout << "Please enter a valid number" << endl;
            break;
        }
    }
}
void UserInterface::createIndex()
{
    auto start = high_resolution_clock::now();
    cout << "Please enter path for documents" << endl;
    string path;
    cin >> path;
    cout << "Creating index..." << endl;
    Parser parser;
    
    parser.fileSystem(path, wordTree, people, orgs, stopWords);
    numDocs = parser.getNumDocs();

    auto stop = high_resolution_clock::now();
    time = duration_cast<microseconds>(stop - start);
    return;
}
void UserInterface::writeIndex()
{
    cout << "Writing index to file..." << endl;
    Index index;
    index.makeIndex(wordTree, people, orgs);
    return;
}
void UserInterface::readIndex()
{
    cout << "Reading index from persistence..." << endl;
    Index index;
    index.readIndex(wordTree);
    //index.readOrg(orgs);
    index.readPerson(people);
    return;
}
void UserInterface::enterQuery()
{
    cout << "Enter query: ";
    string choice;
    cin.ignore();
    cin.clear();
    getline(cin, choice);
    Query query;
    query.parseQuery(choice, wordTree, people, orgs, stopWords, finalDocs);
    if (finalDocs.empty())
    {
        cout << "No results found" << endl;
    }
    else
    {
        relevancyRanking(finalDocs);
        int i = 0;
        for (auto &d : finalDocs)
        {
            cout << i + 1 << endl;
            cout << "Title: " << d.first->title << endl;
            cout << "UUID: " << d.first->uuid << endl;
            cout << "Author: " << d.first->author << endl;
            cout << "Published: " << d.first->published << endl;
            cout << endl;
            i++;
            if (i >= 15)
                break;
        }
        while (true)
        {
            cout << "Enter the document number you want to view. Enter to 0 to return to menu" << endl;
            string num;
            cin >> num;
            int numInt = stoi(num);
            if (numInt < 0 || numInt > finalDocs.size())
            {
                cout << "Please enter a valid document number" << endl;
                continue;
            }
            if (numInt == 0)
            {
                break;
            }
            cout << "Text: " << finalDocs.at(numInt - 1).first->text << endl;
        }
    }

    return;
}
void UserInterface::outputStatistics()
{
    cout << "Statistics:" << endl;
    cout << "Time taken to index: " << time.count() << " microseconds" << endl;
    cout << "Total Number of Unique words: " << wordTree.size() << endl;
    cout << "Total Number of Documents: " << numDocs << endl;
    cout << "Total Number of People: " << people.size() << endl;
    cout << "Total Number of Orgs: " << orgs.size() << endl;

    wordTree.makeEmpty();

    return;
}
void UserInterface::relevancyRanking(vector<pair<shared_ptr<Doc>, int>> &finalDocs)
{
    float df = finalDocs.size();
    float N = numDocs;
    float idf = log10(N / df);
    float tf;    // tf is the term frequency
    float score; // Score will be computed by multiplying tf and idf
    for (auto &d : finalDocs)
    {
        tf = d.second;
        score = tf * idf;
        d.first->rank = score;
    }
    sort(finalDocs.begin(), finalDocs.end());
}
