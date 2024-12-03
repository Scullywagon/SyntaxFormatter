#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void inputIndents();
void newLine();
void includes();
void makeLine();
void doTabs();

bool inArgs;
bool inIncludes;
bool startLine;

ifstream infile;
ofstream outfile("outfile.c");
string line;
int indentCount = 0;

int main (int argc, char* argv[])
{
    int spaceCount = 0;

    startLine = true;
    inArgs = false;
    inIncludes = false;

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    infile.open(argv[1]);

    char c;
    // iterate over each line
    while (infile.get(c)) 
    {
        if (c == '#')
        {
            startLine = false;
            inIncludes = true;
            outfile << c;
        }
        else if (inIncludes == true && c == '>')
        {
            outfile << c << "\n\n";
            startLine = true;
        }
        else if (c == '{')
        {
            startLine = true;
            outfile << '\n';
            doTabs();
            outfile << c << '\n';
            indentCount++;
        }
        else if (c == '}')
        {
            indentCount--;
            doTabs();
            outfile << c << "\n\n";
            startLine = true;
        }
        else if (c == '(')
        {
            outfile << c << " ";
            inArgs = true;
        }
        else if (c == ')')
        {
            outfile << " " << c;
            inArgs = false;
        }
        else if (c == ';')
        {
            if (inArgs != true)
            {
                outfile << c << '\n';
                startLine = true;
            }
            else
            {
                outfile << c;
            }
        }
        else if (c == '\n')
        {
            continue;
        }
        else if (c == ' ' && startLine == true)
        {
            continue;
        }
        else if (c == ' ')
        {
            if (spaceCount > 0) continue;
            outfile << c;
            spaceCount++;
        }
        else
        {
            spaceCount = 0;
            if (startLine == true)
            {
                doTabs();
                startLine = false;
            }
            outfile << c;
        }
    }
}

void doTabs()
{
    for (int i = 0; i < indentCount; i++)
    {
        outfile << '\t';
    }
}