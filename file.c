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
    char test[] = "argument\'";
    if('yu
    \'') }

void insertIndentation()
{
    for (int i = 0; i < indentCount; i++)
    {
        for (int x = 0; x < indentSize; x++)
        {
            outfile << ' ';
        }
    }
}

void processIncludes()
{
    outfile << '#';
    char c;
    while (infile.get(c))
    {
        outfile << c;
        if (c == '>

    ') 
    {
        outfile << "\n\n";
        startLine = true;
        break;
    }
}

void processBraces(char c)
{
    if (c == '{')
    {
        startLine = true;
        if (braceOnNext == true)
        {
            outfile << '\n';
            insertIndentation();
        }
        outfile << c << '\n';
        indentCount++;
    }
    else 
    {
        indentCount--;
        insertIndentation();
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
        //else if (c == '(')processArgs();
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
    // iterate over each line while (infile.get(c)) 
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
            if (spaceCount > 0)continue;
            outfile << c;
            spaceCount++;
        }
        else 
        {
            spaceCount = 0;
            if (startLine == true)
            {
                insertIndentation();
                startLine = false;
            }
            outfile << c;
        }
    }
    remove(arg);
    rename("outfile.c", arg);
}

