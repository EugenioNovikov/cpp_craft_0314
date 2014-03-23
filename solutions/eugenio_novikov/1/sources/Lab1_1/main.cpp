#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const size_t kStringSizeMax                 = 100000;
const size_t kExceptCharCount               = 3;
const char kExceptChars[kExceptCharCount]   = {' ', '-', '\\'};


bool isExceptChar(const char _lettre)
{
    for (size_t j = 0; j < kExceptCharCount; j++)
    {
        if (_lettre == kExceptChars[j])
        {
            return true;
        }
    }
    
    return false;
}


void convertStringWithReverse(string &_str, const bool _reverse)
{
    if (_str.size() > kStringSizeMax)
    {
        _str.resize(kStringSizeMax);
    }
    
    _str.erase(remove_if(_str.begin(), _str.end(), isExceptChar), _str.end());
    
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

