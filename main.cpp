#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <vector>
//Globals
bool readAndParseCmdLine(char * &prog, char * args[], std::string & input)
{
    std::cout << "Bash> ";
    input = "";
    std::getline (std::cin,input);
    if (input.length() == 0)
        return false;
    
    
    args[0] = ((char *) input.substr(0, input.find(' ')).c_str());
    if (input.find('-') > -1)
        args[1] = ((char *) input.substr(input.find('-')).c_str());
    prog = args[0];
    int child_pid = fork();
    if (child_pid == 0)
        {
            //Child Process
            execvp(prog, args);
        }
        else
        {
            //Parent - waits
            wait(&child_pid);
            return true;
        }
}

int main()
{
    char * prog = NULL;
    char * args[] = {NULL, NULL, NULL};
    std::string input = "";
    // Read the input a line at a time and parse it into the program name and
    //its arguments. End loop if we have reached the end of input

    while(readAndParseCmdLine(prog, args, input))
    {
        args[0] = NULL;
        args[1] = NULL;
        continue;
    }
}
