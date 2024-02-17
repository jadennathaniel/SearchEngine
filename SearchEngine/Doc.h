#ifndef DOC_H
#define DOC_H

#include <string>
using namespace std;

struct Doc
{
    string title;
    string uuid;
    string published;
    string author;
    string text;
    int rank;

    Doc(){};
    Doc(string t, string u, string p, string a, string w) : title(t), uuid(u), published(p), author(a), text(w){};

    bool operator==(const Doc &d) const
    {
        return title == d.title && uuid == d.uuid && published == d.published && author == d.author && rank == d.rank && text == d.text;
    }
    bool operator<(const Doc &d) const 
    {
        return (d.rank < rank);
    }

    bool operator>(const Doc &d) const
    {
        return (d.rank > rank);
    }
};

#endif