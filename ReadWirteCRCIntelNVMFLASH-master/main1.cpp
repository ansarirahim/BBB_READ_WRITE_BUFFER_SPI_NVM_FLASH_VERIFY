#include <iostream>
#define DATA_LENGTH 0
#define ADDRESS_START_INDEX DATA_LENGTH + 1
#define ADDRESS_NO_OF_BYTES 2
#define RECORD_DATA_TYPE_DATA 0  //DATA RECORED
#define RECORD_DATA_TYPE_EOF 1   //END OF FILE
#define RECORD_DATA_TYPE_ESA 2   //EXTENDED START ADDRESS
#define RECORD_DATA_TYPE_INDEX 3 //
#define RECORD_DATA_TYPE_ELA 4   //EXTENDED LINEAR ADDRESS
#define RECORD_DATA_TYPE_SLA 5   //START LINEAR ADDRESS
#define RECORD_DATA_STARTED_INDEX 4
using namespace std;
unsigned int lineCounter;

//int main()
//{int i=0;
//    while(1){
//    cout << "Hello world!" << endl;
//    i++;
//
//    }
//    return 0;
//}


typedef unsigned char BYTE;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;
struct LineData
{
    // Store bytes read in current line
    vector<BYTE> Data;
};
#define DATA_LENGTH 0
#define ADDRESS_START_INDEX DATA_LENGTH + 1
#define ADDRESS_NO_OF_BYTES 2
#define RECORD_DATA_TYPE_DATA 0  //DATA RECORED
#define RECORD_DATA_TYPE_EOF 1   //END OF FILE
#define RECORD_DATA_TYPE_ESA 2   //EXTENDED START ADDRESS
#define RECORD_DATA_TYPE_INDEX 3 //
#define RECORD_DATA_TYPE_ELA 4   //EXTENDED LINEAR ADDRESS
#define RECORD_DATA_TYPE_SLA 5   //START LINEAR ADDRESS
#define RECORD_DATA_STARTED_INDEX 4
unsigned int temp=0;
//
// *** DATA STRUCTURES ***
//

// Each line data is stored in this structure

BYTE CharToHex(char ch)
{
    // Convert to upper case
    ch = toupper(ch);

    // Parse nibble
    if (ch >= '0' && ch <= '9')
    {
        return (ch - '0');
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return (ch - 'A' + 10);
    }
    else
    {
        // Bad input character
        assert(false);
        return 0; // to suppress warning C4715
    }
}
BYTE ParseByte(const char *str)
{
    char highNibbleChar = str[0];
    char lowNibbleChar = str[1];

    BYTE highNibble = CharToHex(highNibbleChar);
    BYTE lowNibble = CharToHex(lowNibbleChar);

    return (lowNibble + (highNibble << 4));
}

void ParseLine(const string &line, vector<BYTE> &data)
{
    // Clear vector content
    data.clear();

    //
    const char *ptr = line.c_str();

    // Skip starting ":"
    assert(*ptr == ':');
    ptr++;

    // String length.
    // Process characters two-by-two; exclude starting ":" (so: length-1)
    int byteCount = (line.length() - 1) / 2;

    // Reserve storage in array
    data.reserve(byteCount);

    // Process each couple of hex chars in the string
    for (int i = 0; i < byteCount; i++)
    {
        // Parse couples of hex characters and convert them to bytes
        BYTE currByte = ParseByte(ptr);

        // Add byte to array
        data.push_back(currByte);

        // Go to next characters
        ptr += 2;
    }
    // printf("\n");
    // for(int i=0;i<byteCount;i++)
    // printf(" %.2X",data.at(i));
}
unsigned int  extendedLA=0;
unsigned int requestedELA=0;
unsigned int pageNo=0;
unsigned int requestedPageNo=0;
unsigned int pageIndex=0;
#include <string>
BYTE tempPageData[256];
int main(int argc, char **argv)
{

  
    if(argc!=6)
    {printf("\nNACK");
    return 0;
    }
      char fileName[100];
    for(int i=0;i<100;i++)
    {
        fileName[i]=argv[1][i];
        if(argv[1][i]=='\0')
        break;
    }
   
     //argv[1];
requestedELA=atol(argv[2]);
requestedPageNo=atol(argv[3]);
int fromIndex=atol(argv[4])%256;
int toIndex=atol(argv[5])%256;

printf("\nrequestedELA =%.2X requestedPageNo=%.2X",requestedELA,requestedPageNo);
    ///

    ///

    // Try opening input text file
    ifstream inFile(fileName);//0010603_FLASH.HEX"); //InputFile.txt");

    // Check for open failure
    if (!inFile)
    {
        cout << "Can't open file." << endl;
        exit(1);
    }

    // Line read from file
    string line;

    // Store data read from file, line by line
    vector<LineData> fileData;
    // struct pageData
    // {
    //     BYTE page[256];
    //     unsigned int pageNo;
    //     unsigned int exAddres;
    // };
    // vector <pageData> myPageData;
    // Read file line by line, and process it
    while (getline(inFile, line))
    {

        LineData currLineData;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);
        lineCounter++;
    }
for (int j = 0; j < lineCounter; j++)
    {
        /// printf("\n");

        switch (fileData.at(j).Data.at(RECORD_DATA_TYPE_INDEX))
        {
        case RECORD_DATA_TYPE_DATA:
pageNo=fileData.at(j).Data.at(1);
pageIndex=fileData.at(j).Data.at(2);

    if((extendedLA==requestedELA)&&(pageNo==requestedPageNo))
    {
printf("\nretreived Pageno =%.2X Retrived pageindex=%.2X,eLA=%u",pageNo,pageIndex,extendedLA);

            for (int i = 0; i < fileData.at(j).Data.at(DATA_LENGTH); i++)
            {
               /// printf("%.2X",fileData.at(j).Data.at(4+i));
          tempPageData[pageIndex+i]=fileData.at(j).Data.at(4+i);
          
            ///    if((pageIndex%16==0) ||(pageIndex==255))
                {
                if((pageIndex+i)==255)
                    break;
                }
               //  temp++;

            }
    }

            break;
        case RECORD_DATA_TYPE_EOF:
           /// printf("\nFinished file");
            // exit(0);
            break;
        case RECORD_DATA_TYPE_ESA:
            printf("\nesa");
            break;
        case RECORD_DATA_TYPE_ELA:

        extendedLA=((unsigned int)fileData.at(j).Data.at(4)) * 16 + (unsigned int)fileData.at(j).Data.at(5);
            break;
        case RECORD_DATA_TYPE_SLA:
            printf("\nsla");
            break;
        }
    }
    printf("\n");
    for(int i=fromIndex;i<=toIndex;i++){
    if(i%16==0)
    printf("\n");
    printf("%.2X",tempPageData[i]);
    }


}
