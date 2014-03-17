//
//  main.cpp
//  Lab1_2
//
//  Created by Eugenio on 16.03.14.
//  Copyright (c) 2014 Eugenio. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

//#define PROJECT_PATH "/Users/newmango/Documents/C++Craft/Solutions/1/Lab1_2/"
//
//
//const string kInpuFilePath                  = PROJECT_PATH "input.txt";
//const string kOutpuFilePath                 = PROJECT_PATH "output.txt";

const size_t kCodeCountMax                  = 1000000;
const float kAccuracy                       = 1e-4;




int main(int argc, const char * argv[])
{
    ifstream inputFile(BINARY_DIR "/input.txt");
    ofstream outputFile(BINARY_DIR "/output.txt");

    if (inputFile.is_open())
    {
        set<float> codeSet;
        
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
            float codeValue = 0;
            float passwordValue = 0;
            
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
                
                for (std::set<float>::iterator codeIterator = codeSet.begin(); codeIterator != codeSet.end(); codeIterator++)
                {
                    if (fabsf((*codeIterator) - passwordValue) < kAccuracy)
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

