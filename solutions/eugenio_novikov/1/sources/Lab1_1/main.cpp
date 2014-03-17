//
//  main.cpp
//  Lab1_1
//
//  Created by Eugenio on 16.03.14.
//  Copyright (c) 2014 Eugenio. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//#define PROJECT_PATH "/Users/newmango/Documents/C++Craft/Solutions/1/Lab1_1/"


const size_t kStringSizeMax                 = 100000;
const size_t kExceptCharCount               = 3;
const char kExceptChars[kExceptCharCount]   = {' ', '-', '\\'};
//const string kInpuFilePath                  = PROJECT_PATH "input.txt";
//const string kOutpuFilePath                 = PROJECT_PATH "output.txt";


void convertStringWithReverse(string &_str, bool _reverse)
{
    if (_str.size() > kStringSizeMax)
    {
        _str.resize(kStringSizeMax);
    }
    
    for (size_t j = 0; j < kExceptCharCount; j++)
    {
        long iterator = _str.find(kExceptChars[j]);
        
        while (iterator < _str.length())
        {
            _str.erase(iterator, 1);
            
            iterator = _str.find(kExceptChars[j]);
        }
    }
    
    transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
    
    if (_reverse)
    {
        reverse(_str.begin(), _str.end());
    }
}


int main(int argc, const char * argv[])
{
    ifstream inputFile(BINARY_DIR "/input.txt");
    ofstream outputFile(BINARY_DIR "/output.txt");
    
    if (inputFile.is_open())
    {
        string firstLineInputFile = "";
        string nextLineInputFile = "";
        
        size_t lineNumber = 0;
        
        while (!inputFile.eof())
        {
            if (lineNumber == 0)
            {
                getline(inputFile, firstLineInputFile);
                convertStringWithReverse(firstLineInputFile, false);
            }
            else
            {
                getline(inputFile, nextLineInputFile);
                convertStringWithReverse(nextLineInputFile, true);
                
                if (firstLineInputFile.find(nextLineInputFile) != string::npos && firstLineInputFile.size() > 0)
                {
                    outputFile << "YES" << "\n";
                }
                else
                {
                    outputFile << "NO" << "\n";
                }
            }

            lineNumber++;
        }
    }
    
    inputFile.close();
    outputFile.close();

    return 0;
}

