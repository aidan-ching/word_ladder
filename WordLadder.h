#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <string>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

class WordLadder{
    private:
    list<string> dict;
    bool compareString(const string &, const string &);

    public:
    WordLadder(const string &);
    void outputLadder(const string &start, const string &end, const string &outputFile);
};

#endif