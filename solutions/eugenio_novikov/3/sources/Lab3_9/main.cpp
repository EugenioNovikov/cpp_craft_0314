#include <iostream>
#include <fstream>
#include "stock_data.h"
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/ref.hpp>

using namespace std;


static boost::mutex __mtx;

void writeStockData(const binary_reader::stock_data &stockData)
{
    boost::mutex::scoped_lock scoped_lock(__mtx);
    
    string outFileName = "/input.txt" + string(stockData.stock_name()) + ".txt";
    ofstream outFile(outFileName, ios::binary);
    
    stockData.write(outFile);
}


int main(int argc, char* argv[])
{
    ifstream inFile("/input.txt", ios::binary);
    
    try {
        
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
                
                boost::thread thrd(writeStockData, boost::ref(stockData));
                thrd.join();
            }
            
            inFile.close();
        }
    }
    catch (std::exception &exception_)
    {
        cerr << exception_.what() << endl;
    }
    
	return 0;
}
