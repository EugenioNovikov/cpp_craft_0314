#include <iostream>
#include <fstream>
#include "stock_data.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream inFile(BINARY_DIR "/input.txt", ios::binary);
    ofstream outFile(BINARY_DIR "/output.txt", ios::binary);

    
    if (inFile.is_open())
    {
        inFile.seekg(0, ios::end);
        const size_t inputFileSize = inFile.tellg();
        inFile.seekg(0);
        size_t curPosition = inFile.tellg();
    
        while (curPosition < inputFileSize)
		{
            binary_reader::stock_data stockData(inFile);
            curPosition = inFile.tellg();
            
            stockData.write(outFile);
		}
    }
    else
    {
        throw (logic_error("file is closed"));
    }
    
    inFile.close();
    outFile.close();
    
	return 0;
}
