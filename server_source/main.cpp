#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <regex>
#include "led.h"
#include "fifopipe.h"


using namespace std;

bool isDec(const string &s);

int main (int argc, char ** argv)
{

    Led *led = new Led();
    string str;
    string token = "exit";
    string words[1000];
    while(words[0] != token)
    {
        Fifopipe *fifopipe = new Fifopipe();
        str = "";
		words[0] = "";
		words[1] = "";
        bool validInputs = true;
        str = fifopipe->ReadFromPipe();


        //**************************************************
        //
        if (!str.empty())
        {
            cout << "STRING: " << str << endl;
            istringstream ist(str);
            string tmp;
            int count = 0;
            while ( ist >> tmp )
            {
                words[count] = tmp;
                count++;
                if (count > 3)
                {
                    fifopipe->WriteToPipe("Too many arguments!\n");
                    validInputs = false;
                }
            }
            cout << "Command: " << words[0] << " argument: " << words[1] << endl;
            //**************************************************
            //
            if (validInputs)
            {
                if (words[0] == "set-led-state")
                {
                    if (words[1] == "on" || words[1] == "off")
                    {
                        led->setLedState(words[1]);
                        fifopipe->WriteToPipe("OK\n");
                    }
                    else
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                }
                else if (words[0] == "get-led-state")
                {
                    if (!words[1].empty())
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                    else
                    {
                        string str;
                        str.append("OK ");
                        str.append(led->ledState());
                        str.append("\n");
                        fifopipe->WriteToPipe(str);
                    }
                }
                else if (words[0] == "set-led-color")
                {
                    bool check = false;
                    for (int i = 0; i < 3; i++)
                    {
                        if (words[1] == led->colorList(i))
                        {
                            led->setLedColor(words[1]);
                            check = true;
                            break;
                        }
                    }
                    if (check)
                    {
                        fifopipe->WriteToPipe("OK\n");
                    }
                    else
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                }
                else if (words[0] == "get-led-color")
                {
                    if (!words[1].empty())
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                    else
                    {
                        string str;
                        str.append("OK ");
                        str.append(led->ledColor());
                        str.append("\n");
                        fifopipe->WriteToPipe(str);
                    }
                }
                else if (words[0] == "set-led-rate")
                {
                    string str;
                    str = words[1];
                    if (isDec(str))
                    {
                        int intStr = stoi(str);
                        if (intStr >= 0 && intStr <= 5)
                        {
                            led->setLedRate(intStr);
                            fifopipe->WriteToPipe("OK\n");
                        }
                        else
                        {
                            fifopipe->WriteToPipe("Failed\n");
                        }
                    }
                    else
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                }
                else if (words[0] == "get-led-rate")
                {
                    if (words[1] == "")
                    {
                        fifopipe->WriteToPipe("Failed\n");
                    }
                    else
                    {
                        string str;
                        str.append("OK ");
                        str.append(to_string(led->ledRate()));
                        str.append("\n");
                        fifopipe->WriteToPipe(str);
                    }
                }
                else
                {
                    fifopipe->WriteToPipe("Failed. Invalid command.\n");
                }
            }
        }
        delete fifopipe;
    }
    //**************************************************

    return 0;
}

bool isDec(const string &s)
{
    regex reg("[0-9]");
    if (regex_match(s, reg))
    {
        return true;
    }
    return false;
}

