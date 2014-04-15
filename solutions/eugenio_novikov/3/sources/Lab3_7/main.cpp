#include <iostream>
#include <fstream>
#include <iostream>
#include <market_message.h>
#include <algorithm>
#include <boost/thread.hpp>

using namespace std;

const boost::uint32_t kTimeStep     = 2;
const long kMessageMaxCount         = 1e+16;

const size_t kFileMaxNumber         = 999;

typedef enum
{
    MARKET_OPEN     = 1,
    TRADE           = 2,
    QUOTE           = 3,
    MARKET_CLOSE    = 4
    
} messageType;



class fileHandler
{
    size_t fileIndex_;
    
public:
    
    fileHandler(size_t _fileIndex):fileIndex_(_fileIndex)
    {
        
    }
    
    void handle()
    {
        string endFileName = stringFromNumber(fileIndex_);
        
        ifstream inFile(BINARY_DIR "/input_" + endFileName + ".txt", ios::binary);
        ofstream outFile(BINARY_DIR "/output_" + endFileName + ".txt", ios::binary);
        
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
                    marketMessage.write(outFile);
                    maxTime = std::max(maxTime, marketMessage.time());
                }
                
                messageCount++;
            }
        }
        else
        {
            throw (logic_error("file is closed"));
        }
        
        inFile.close();
        outFile.close();
    }
    
    
private:
    
    bool isActualMessageTime(const boost::uint32_t _mTime, const boost::uint32_t _maxTime)
    {
        return _mTime + kTimeStep > _maxTime;
    }
    
    
    bool isActuelaMessageType(const boost::uint32_t _mType)
    {
        return (_mType >= MARKET_OPEN && _mType <= MARKET_CLOSE);
    }
    
    
    string stringFromNumber(const size_t _number)
    {
        string number = boost::to_string(_number);
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
};


int main(int argc, const char * argv[])
{
    try
    {
        for (size_t j = 1; j <= kFileMaxNumber; j++)
        {
            fileHandler handler = j;
            
            boost::thread newThread(&fileHandler::handle, &handler);
            newThread.join();
        }
    }
    catch (std::exception &exception_)
    {
        cerr << exception_.what() << endl;
    }
    
    return 0;
}
