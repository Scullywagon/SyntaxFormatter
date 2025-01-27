#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


// settings
bool argSpace = true;
bool braceOnNext = false;

// Declaring functions
void inputIndents();
void processFile(char* arg);
void doTabs();

// File init
ifstream infile;
ofstream outfile("outfile.c");

// Trackers
int indentCount = 0;
int spaceCount = 0;
bool inArgs;
bool startLine;


// main method
int main (int argc, char* argv[])
{

    startLine = true;
    inArgs = false;

    if (argc <= 1)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        processFile(argv[i]);
    }
   
}

void doTabs()
{
    for (int i = 0; i < indentCount; i++)
    {
        outfile << '\t';
    }
}

void processIncludes()
{
    outfile << '#';
    char c;
    while (infile.get(c))
    {
        outfile << c;
        if (c == '>')
        {
            outfile << "\n\n";
            startLine = true;
            break;
        }
    }
}

void processBraces(char c)
{
    if (c == '{')
    {
        startLine = true;
        outfile << '\n';
        doTabs();
        outfile << c << '\n';
        indentCount++;
    }
    else 
    {
        indentCount--;
        doTabs();
        outfile << c << "\n\n";
        startLine = true;
    }
}

void processArgs()
{
    outfile << '(';
    char c;
    if (argSpace == true)
    {
        outfile << ' ';
    }    
    while (infile.get(c))
    {
        if (c == ')') break;
        //else if (c == '(') processArgs();
        outfile << c;
    }
    if (argSpace == true)
    {
        outfile << ' ';
    }
    outfile << ")";
}


void processFile(char* arg)
{
    infile.open(arg);

    char c;
    // iterate over each line
    while (infile.get(c)) 
    {
        if (c == '#')
        {
            processIncludes();
        }
        else if (c == '{' || c == '}')
        {
            processBraces(c);
        }
        else if (c == '(')
        {
            processArgs();
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
    remove(arg);
    rename("outfile.c", arg);
}