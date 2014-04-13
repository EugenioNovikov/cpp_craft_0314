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
		while (!inFile.eof())
		{
            binary_reader::stock_data stockData(inFile);
        
            stockData.write(outFile);
		}
        
		inFile.close();
		outFile.close();
	}
    
	return 0;
}
