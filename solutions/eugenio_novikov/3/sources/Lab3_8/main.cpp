#include <iostream>
#include <fstream>
#include <iostream>
#include <market_message.h>
#include <algorithm>
#include <map>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

static boost::mutex __mtx;

const boost::uint32_t kMaxType                  = 100000;
const boost::uint32_t kMaxTotalSizeOfMessage    = 2048;

const size_t kFileMaxNumber                     = 999;


#define BINARY_DIR "ssd"

namespace file_processing
{
    string stringFromNumber(const size_t _number)
    {
        string number = to_string(_number);
        string result = "";
        
        if (_number < 10)
        {
            result = "00";
        }
        else if(_number < 100)
        {
            result = "0";
        }
        
        return result + number;
    }
    
    
    void fileProcessingWithFileID(const size_t _id)
    {
        boost::mutex::scoped_lock scoped_lock(__mtx);
        
        string endFileName = stringFromNumber(_id);
        
        ifstream inFile(BINARY_DIR "/input_" + endFileName + ".txt", ios::binary);
        ofstream outFile(BINARY_DIR "/output_.txt", ios::binary);
        
        if (inFile.is_open())
        {
            boost::uint32_t currentTime = 0;
            
            inFile.seekg(0, ios::end);
            const size_t inputFileSize = inFile.tellg();
            inFile.seekg(0);
            size_t curPosition = inFile.tellg();
            
            map<boost::uint32_t, boost::uint32_t> messageCounter;
            map<boost::uint32_t, boost::uint32_t> messageManager;
            map<boost::uint32_t, boost::uint32_t> messageActiveSeconds;
            
            while (curPosition < inputFileSize)
            {
                binary_reader::market_message marketMessage(inFile);
                curPosition = inFile.tellg();
                
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
                        if (messageManager[marketMessageType] == 0)
                        {
                            messageActiveSeconds[marketMessageType]++;
                        }
                        
                        messageManager[marketMessageType] += marketMessage.messageSize();
                        
                        messageCounter[marketMessageType]++;
                    }
                }
            }
            
            for (map<boost::uint32_t, boost::uint32_t>::iterator iterator = messageCounter.begin(); iterator != messageCounter.end(); iterator++)
            {
                boost::uint32_t type = iterator->first;
                boost::uint32_t activeSeconds = messageActiveSeconds[type];
                
                if (activeSeconds == 0)
                {
                    cerr << "activeSeconds = 0";
                }
                
                double averageCount = (double)(iterator->second) / (activeSeconds);
                
                outFile.write( reinterpret_cast< char* >(&type), sizeof(type));
                outFile.write( reinterpret_cast< char* >(&averageCount), sizeof(averageCount));
            }
        }
        
        inFile.close();
        outFile.close();
    }
}


int main(int argc, const char * argv[])
{
    try
    {
        for (size_t j = 1; j <= kFileMaxNumber; j++)
        {
            boost::thread newThread(&file_processing::fileProcessingWithFileID, j);
            newThread.join();
        }
    }
    catch (std::exception &exception_)
    {
        cerr << exception_.what() << endl;
    }
    
    return 0;
}