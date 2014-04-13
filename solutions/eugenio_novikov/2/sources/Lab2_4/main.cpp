#include <iostream>
#include <fstream>
#include <iostream>
#include <market_message.h>
#include <algorithm>

using namespace std;

const boost::uint32_t kTimeStep = 2;
const long kMessageMaxCount = 1e+16;


typedef enum
{
    MARKET_OPEN     = 1,
    TRADE           = 2,
    QUOTE           = 3,
    MARKET_CLOSE    = 4

} messageType;


bool isActualMessageTime(const boost::uint32_t _mTime, const boost::uint32_t _maxTime)
{
    return _mTime + kTimeStep > _maxTime;
}


bool isActuelaMessageType(const boost::uint32_t _mType)
{
    return (_mType >= MARKET_OPEN && _mType <= MARKET_CLOSE);
}


int main(int argc, const char * argv[])
{
    ifstream inFile(BINARY_DIR "/input.txt", ios::binary);
    ofstream outFile(BINARY_DIR "/output.txt", ios::binary);
    
    if (inFile.is_open())
    {
        boost::uint32_t maxTime = 0;
        long messageCount = 0;
     
        inFile.seekg(0, ios::end);
        const size_t inputFileSize = inFile.tellg();
        inFile.seekg(0);
        size_t curPosition = inFile.tellg();
        
        
        while (curPosition < inputFileSize && messageCount <= kMessageMaxCount)
        {
            binary_reader::market_message marketMessage(inFile);
            curPosition = inFile.tellg();
            
            if(isActuelaMessageType(marketMessage.type()) && isActualMessageTime(marketMessage.time(), maxTime))
            {
                maxTime = std::max(maxTime, marketMessage.time());
                marketMessage.write(outFile);
            }
            
            messageCount++;
        }
    }
    
    inFile.close();
    outFile.close();
    
    return 0;
}

