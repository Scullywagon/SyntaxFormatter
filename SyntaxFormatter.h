#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// settings
bool argSpace = false;
bool braceOnNext = true;
int indentSize = 4;

// File init
ifstream infile;
ofstream outfile("outfile.c");

// Trackers
int indentCount = 0;
int spaceCount = 0;
bool inArgs;
bool startLine;

int main (int argc, char* argv[]);
void insertIndentation();
void processIncludes();
void processBraces(char c);
void processArgs();
void processFile(char* arg);