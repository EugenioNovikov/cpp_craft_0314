#include <iostream>
#include <fstream>
#include <iostream>
#include <market_message.h>
#include <algorithm>
#include <map>

using namespace std;

const boost::uint32_t kMaxType                  = 100000;
const boost::uint32_t kMaxTotalSizeOfMessage    = 2048;


int main(int argc, const char * argv[])
{
    ifstream inFile(BINARY_DIR "/input.txt", ios::binary);
    ofstream outFile(BINARY_DIR "/input.txt", ios::binary);
    
    if (inFile.is_open())
    {
        boost::uint32_t currentTime = 0;
        
        map<boost::uint32_t, boost::uint32_t> messageCounter;
        map<boost::uint32_t, boost::uint32_t> messageManager;
        
        while (!inFile.eof())
        {
            binary_reader::market_message marketMessage(inFile);
            
            boost::uint32_t marketMessageType = marketMessage.type();
            
            if (marketMessageType <= kMaxType)
            {
                if (currentTime != marketMessage.time())
                {
                    currentTime = marketMessage.time();
                    
                    for (map<boost::uint32_t, boost::uint32_t>::iterator iterator = messageManager.begin(); iterator != messageManager.end(); iterator++)
                    {
                        iterator->second = 0;
                    }
                }
                
                if (messageManager[marketMessageType] + marketMessage.messageSize() <= kMaxTotalSizeOfMessage)
                {
                    messageManager[marketMessageType] += marketMessage.messageSize();
                    
                    messageCounter[marketMessageType]++;
                }
            }
        }
        
        for (map<boost::uint32_t, boost::uint32_t>::iterator iterator = messageCounter.begin(); iterator != messageCounter.end(); iterator++)
        {
            boost::uint32_t type = iterator->first;
            double averageCount = (double)(iterator->second) / (currentTime + 1);
            
            outFile.write( reinterpret_cast< char* >(&type), sizeof(type));
            outFile.write( reinterpret_cast< char* >(&averageCount), sizeof(averageCount));
        }
    }
    
    inFile.close();
    outFile.close();
    
    return 0;
}