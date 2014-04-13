#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

const size_t kCodeCountMax                  = 1000000;
const double kAccuracy                      = 1e-4;


int main(int argc, const char * argv[])
{
    ifstream inputFile(BINARY_DIR "/input.txt");
    ofstream outputFile(BINARY_DIR "/output.txt");
    
    if (inputFile.is_open())
    {
        set<double> codeSet;
        
        int codeCount = 0;
        inputFile >> codeCount;

        if (codeCount > 0)
        {
            if (codeCount > kCodeCountMax)
            {
                outputFile << "Warning: codeCount is too large \n";
                
                codeCount = kCodeCountMax;
            }
            
            size_t currentLine = 0;
            double codeValue = 0;
            double passwordValue = 0;
            
            while (!inputFile.eof() && currentLine < codeCount)
            {
                inputFile >> codeValue;
                
                if (currentLine < codeCount)
                {
                    codeSet.insert(codeValue);
                }
                
                currentLine++;
            }
        
            bool isEqualCodeAndPassword = false;
            
            while (!inputFile.eof())
            {
                inputFile >> passwordValue;
                
                for (std::set<double>::iterator codeIterator = codeSet.begin(); codeIterator != codeSet.end(); codeIterator++)
                {
                    if (fabs((*codeIterator) - passwordValue) < kAccuracy)
                    {
                        isEqualCodeAndPassword = true;
                        
                        break;
                    }
                }
                
                if (isEqualCodeAndPassword)
                {
                    outputFile << "YES" << "\n";
                    isEqualCodeAndPassword = false;
                }
                else
                {
                    outputFile << "NO" << "\n";
                }
            }
        }
        else
        {
            outputFile << "incorrect input file \n";
        }
    }
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}

