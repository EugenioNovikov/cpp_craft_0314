#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;


const char kLandSymbol                      = 'o';
const char kWaterSymbol                     = '~';

static size_t columnCount = 0;
static size_t rowCount = 0;

void findTotalLand(vector<string> &_layerVector, const size_t _rowNumber, const size_t _columnNumber);

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
        if (_rowNumber + 2 <= rowCount)
        {
            findTotalLand(_layerVector, _rowNumber + 1, _columnNumber);
        }
        if (_columnNumber >= 1)
        {
            findTotalLand(_layerVector, _rowNumber, _columnNumber - 1);
        }
        if (_columnNumber + 2 <= columnCount)
        {
            findTotalLand(_layerVector, _rowNumber, _columnNumber + 1);
        }
    }
}


