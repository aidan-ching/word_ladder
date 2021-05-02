#include "WordLadder.h"

WordLadder::WordLadder(const string &fileName)
{

    string currWord;
    ifstream inputStream;
    inputStream.open(fileName);

    //check if open
    if (!inputStream.is_open())
    {
        cout << "Could not open file " << fileName << "." << endl;
        return;
    }

    while (!inputStream.eof())
    {
        inputStream >> currWord;
        if (!inputStream.fail())
        {
            if (currWord.size() == 5)
            {
                dict.push_back(currWord);
            }
            else
            {
                cout << "Words are not five characters" << endl;
                return;
            }
        }
    }
    inputStream.close();
}

/* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    //check if either words are in the dictionary
    bool doesNotExist = true;
    for (list<string>::iterator i = dict.begin(); i != dict.end(); ++i)
    {
        if (start == *i || end == *i)
        {
            doesNotExist = false;
        }
    }

    if (doesNotExist)
    {
        return;
    }

    //start of word ladder code
    stack<string> first;
    first.push(end);

    queue<stack<string>> ladder;
    ladder.push(first);

    while (!ladder.empty())
    {

        //for each word in the dictionary
        for (list<string>::iterator i = dict.begin(); i != dict.end(); ++i)
        {
            //get the word on top of the front Stack of this Queue
            //if the word is off by just one letter from the top word
            if (compareString(*i, ladder.front().top()))
            {

                //if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder. You are done!
                if (*i == start)
                {
                    //output everything into the file then break
                    ofstream outFS;
                    outFS.open(outputFile);
                    if (!outFS.is_open())
                    {
                        cout << "Could not open " << outputFile << endl;
                        return;
                    }

                    if (start != end)
                    {
                        outFS << start << " ";
                    }

                    while (!ladder.front().empty())
                    {
                        string topOfStack = ladder.front().top();
                        outFS << topOfStack << " ";
                        ladder.front().pop();
                    }

                    outFS.close();

                    return;
                }
                //create a new Stack that is a copy of the front Stack and push on this off-by-one word found
                //otherwise, enqueue this new Stack and remove this word from the dictionary
                else
                {
                    stack<string> temp = ladder.front();
                    temp.push(*i);
                    ladder.push(temp);
                    i = dict.erase(i);
                    i = dict.begin();
                }
            }
        }

        ladder.pop();
    }

    //case where no word ladder exists
    ofstream outFS;
    outFS.open(outputFile);
    if (!outFS.is_open())
    {
        cout << "Could not open " << outputFile << endl;
        return;
    }

    outFS << "No Word Ladder Found.";

    outFS.close();
}

bool WordLadder::compareString(const string &first, const string &second)
{
    int differentChars = 0;
    for (unsigned i = 0; i < first.size(); ++i)
    {
        if (first.at(i) != second.at(i))
        {
            ++differentChars;
        }
    }
    if (differentChars <= 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}