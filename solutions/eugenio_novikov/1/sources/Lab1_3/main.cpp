//
//  main.cpp
//  Lab1_3
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
#include <algorithm>


using namespace std;



//#define PROJECT_PATH "/Users/newmango/Documents/C++Craft/Solutions/1/Lab1_3/"
//
//
//const string kInpuFilePath                  = PROJECT_PATH "input.txt";
//const string kOutpuFilePath                 = PROJECT_PATH "output.txt";

const char kLandSymbol                      = 'o';
const char kWaterSymbol                     = '~';

static size_t columnCount = 0;
static size_t rowCount = 0;

void findTotalLand(vector<string> &_layerVector, size_t _rowNumber, size_t _columnNumber);

//~~o~~o~~o~~~o
//~oo~oooooo~~o
//~~~o~ooo~~~~o
//~~~~oo~~~~~~~
//~ooo~~~~~~~~o

int main(int argc, const char * argv[])
{
    ifstream inputFile(BINARY_DIR "/input.txt");
    ofstream outputFile(BINARY_DIR "/output.txt");
    
    if (inputFile.is_open())
    {
        size_t landCount = 0;
        vector<string> layerVector;

        string firstLine = "";
        
        while (!inputFile.eof())
        {
            getline(inputFile, firstLine);
            layerVector.push_back(firstLine);
        }

        columnCount = firstLine.length();
        rowCount = layerVector.size();
        
        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < columnCount; j++)
            {
                if (layerVector[i][j] == kLandSymbol)
                {
                    landCount++;
                    
                    findTotalLand(layerVector, i, j);
                }
            }
        }
        
        outputFile << landCount;
    }
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}


void findTotalLand(vector<string> &_layerVector, size_t _rowNumber, size_t _columnNumber)
{
    if (_layerVector[_rowNumber][_columnNumber] == kLandSymbol)
    {
        _layerVector[_rowNumber][_columnNumber] = kWaterSymbol;
        
        if (_rowNumber >= 1)
        {
            findTotalLand(_layerVector, _rowNumber - 1, _columnNumber);
        }
        if (_rowNumber < rowCount - 2)
        {
            findTotalLand(_layerVector, _rowNumber + 1, _columnNumber);
        }
        if (_columnNumber >= 1)
        {
            findTotalLand(_layerVector, _rowNumber, _columnNumber - 1);
        }
        if (_columnNumber < columnCount - 2)
        {
            findTotalLand(_layerVector, _rowNumber, _columnNumber + 1);
        }
    }
}


