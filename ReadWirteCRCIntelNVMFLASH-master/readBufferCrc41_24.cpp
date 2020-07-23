//Following is the program is developped by A. R. Ansari
//It will read intel hex file having no extended linear address that is it has maxlimit of 0xFFFF 
/*
command format=
READ_BUFFER_24BIT  <filename> <OFFSET ADDRESS (HEX)>  <PAGE NUMBER (HEX)>  <PAGE NUMBER INDEX(HEX)>  <NUMBER OF BYTES TO BE READ (DECIMAL)>
command example:
READ_BUFFER_24BIT  0010603_FLASH.HEX 4 0 0 256
command expected reply

04 00

FFFF9BFEDBFF2A2B6801DA3A2B6808DA
34351EFA54042B6804121424001CFB31
FB051B141941FB141B1538FB31583AC5
247D000304000DFA4C043500FEFEFEFE
FEFEFEFEC50F040000FAEC3C3C3C1A55
00E1086F02B00D01001F33524B1D3352
4B1F33534B1D33534BC5B6030000C56D
120000C551040000C5330A0000C5DD04
0000C5AB320000C5183D0000C5E52100
00C5E8750000C525540100C57F330000
C5F0340000C5A4250000C5A33F0000C5
0EA60000C5C57B0000C529740000C50A
590000C53B160000C56D420000C57084
0000C5FF450100C548310100FB0970EA
2569FFEA0669FEDA242600317B8EC524


*/
/*

int status = std::system("ls -l >test.txt"); // execute the UNIX command "ls -l >test.txt"
    std::cout << std::ifstream("test.txt").rdbuf();
    std::cout << "Exit code: " << WEXITSTATUS(status) << std::endl;
*/

   #include <unistd.h>
#include <bits/stdc++.h>
#include <cstring>
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

#define SIZE_OF_CURRENT_DIRECTORY_NAME 60
#define PATH_OF_CURRENT_DIRECTORY "/home/debian/BBB_SPI_Clem/ReadWirteCRCIntelNVMFLASH-master/"
using namespace std;
unsigned int lineCounter;
unsigned pageRepeater = 0;
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

//#define OS_Windows 1

int ind=0;
static char fileName[120];
unsigned int temp = 0;
#include <iostream>
std::string getExePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}
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
unsigned int extendedLA = 0;
unsigned int requestedELA = 0;
unsigned int pageNo = 0;
unsigned int requestedPageNo = 0;
unsigned int pageIndex = 0;
#include <string>
BYTE tempPageData[256];
struct pageDetails
{
    BYTE pageData[256];
    BYTE pageNo;
    BYTE extendedLinearAdderess;
    /* data */
};

BYTE extLACounter = 0;
unsigned int pageCounter = 0;
BYTE getNVM_CRC(BYTE *CKBlock, uint32_t Length, BYTE Seed)
{
    BYTE val, y, crc, bbit1;
    uint32_t k;
    crc = Seed;
    for (k = 0; k < Length; k++)
    {
        val = CKBlock[k];
        crc = crc ^ ((val << 4));
        for (y = 0; y < 8; y++)
        {
            bbit1 = crc & 0x80;
            if (bbit1)
            {
                crc = crc ^ 74;
                bbit1 = 1;
            }
            else
                bbit1 = 0;
            crc = ((crc << 1) + bbit1);
        }
        crc = crc ^ 82;
        crc = crc ^ (val >> 4);
    }
    return (crc);
}
BYTE addresshigh, addressmid, addresslow;
int fromIndex, toIndex;
struct newPage
{
    BYTE binaryData[256];
    bool hasData = false;
};
#define NO_OF_NPAGES 256
newPage myNewPages[NO_OF_NPAGES];
struct newFilePageData
{
    newPage myNewPages[256];
};
#define NO_OF_EXTENDED_LA 20
static newFilePageData myNewFilePageData[NO_OF_EXTENDED_LA];
void initDataStructures(newFilePageData arnew[], unsigned int y)
{
    // memset(fileName, '\0', 100);
    ///sprintf(fileName, "%s", PATH_OF_CURRENT_DIRECTORY);
    for (unsigned int i = 0; i < y; i++)
    {
        for (int b = 0; b < 256; b++)
        {
            arnew[i].myNewPages[b].hasData = false;
            memset(arnew[i].myNewPages[b].binaryData, 0xff, 256);
        }
    }
}
char myBytes[2];
unsigned char hex2byte(const char *hex)
{
    unsigned short byte = 0;
    std::istringstream iss(hex);
    iss >> std::hex >> byte;
    return byte % 0x100;
}
char my3Bytes[6];
unsigned char hex3byte(const char *hex)
{
    unsigned int byte = 0;
    std::istringstream iss(hex);
    iss >> std::hex >> byte;
    return byte % 0x1000000;
}
// void xx()
// {
//     #if OS_Windows
//     // windows-specific code goes here
// #else
//     for (; ind < 100; ind++)
//     {
//         if (fileName[ind] == '\0')
//         {
//             break;
//         }
//         ind++;
//     } // linux-specific code
// #endif
//     ///    printf("offset%d=%s\n",ind, fileName);

//     for (int i = 0; i < 100; i++)
//     {

//         fileName[ind + i] = argv[1][i];
//         if (argv[1][i] == '\0')
//             break;
//     }
// }
///static char cwd[100];
int main(int argc, char *argv[])

{
 sprintf(fileName, "%s", getExePath().c_str());//PATH_OF_CURRENT_DIRECTORY);
   for (int i = 0; i < 100; i++)
    {

        fileName[SIZE_OF_CURRENT_DIRECTORY_NAME + i-1] = argv[1][i];
        if (argv[1][i] == '\0')
          { // printf("\n%d",i);
            break;
          }
    }
    //for (int i = 0; argv[2][i]!='\0'; i++)
    int argi=0;
    while(argv[2][argi]!='\0'){
        my3Bytes[argi] = argv[2][argi];
       argi++;
    }
    addresshigh = hex2byte(myBytes);

    for (int i = 0; i < 2; i++)
        myBytes[i] = argv[3][i];
    addresslow = hex2byte(myBytes); //ParseByte(myBytes);

    for (int i = 0; i < 3; i++)
        myBytes[i] = argv[4][i];

    fromIndex = hex2byte(myBytes); //ParseByte(myBytes);

    if (fromIndex >= 256)
        fromIndex = 255;
    toIndex = atoi(argv[5]);
    if (toIndex + fromIndex > 256)
        toIndex = 1;
  

    if (argc != 6)
    {
        printf("\nNACK");
        return 0;
    }
 
   
    

   // printf("full=%s\n", fileName);

//printf("cwd=%s\n",  getcwd(cwd,100));
//std::cout << "\nHi="<<getExePath() << std::endl; 
    ///

    // Try opening input text file
    ifstream inFile(fileName); //0010603_FLASH.HEX"); //InputFile.txt");

    // Check for open failure
    if (!inFile)
    {
        cout << "Can't open file." << endl;
        exit(1);
    }

    // Line read from file
    std::string line;

    vector<LineData> fileData;
    vector<pageDetails> vPageDetails;

    bool endOfFile = false;
    bool dataPresent = true;
    while (getline(inFile, line))
    {

        LineData currLineData;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);

        lineCounter++;
    }
    BYTE lc = 0;
    int checkSumIndex = 0;
    BYTE checkSum = 0;
  initDataStructures(myNewFilePageData, NO_OF_EXTENDED_LA);
    for (int j = 0; j < lineCounter; j++)
    {

        switch (fileData.at(j).Data.at(RECORD_DATA_TYPE_INDEX))
        {
        case RECORD_DATA_TYPE_DATA:
        {
            pageNo = fileData.at(j).Data.at(1);
            pageIndex = fileData.at(j).Data.at(2);
            checkSum = 0;
            for (checkSumIndex = 0; checkSumIndex < fileData.at(j).Data.at(0) + 4; checkSumIndex++)
            {

                checkSum += fileData.at(j).Data.at(checkSumIndex);
            }
            checkSum = ~checkSum;
            checkSum = checkSum + 1;
            ///printf("\n%.2X",fileData.at(j).Data.at(checkSumIndex));
            if (checkSum != fileData.at(j).Data.at(checkSumIndex))
            {
                printf("\nCheckSum Error @LineNo= %u %.2X ", j, checkSum);
                exit(0);
            }

            for (int i = 0; i < fileData.at(j).Data.at(DATA_LENGTH); i++)
            {
                /// printf("%.2X",fileData.at(j).Data.at(4+i));
                if ((i + pageIndex) < 256)
                {
                    myNewFilePageData[extendedLA].myNewPages[pageNo].binaryData[i + pageIndex] = fileData.at(j).Data.at(4 + i);
                }
                else
                {
                    myNewFilePageData[extendedLA].myNewPages[pageNo + 1].binaryData[i + pageIndex] = fileData.at(j).Data.at(4 + i);
                }
            }
        }

        break;
        case RECORD_DATA_TYPE_EOF: //
                                   /// printf("\nFinished file");
            // exit(0);
            break;
        case RECORD_DATA_TYPE_ESA:
            /// printf("\nesa");
            break;
        case RECORD_DATA_TYPE_ELA:

            extendedLA = ((unsigned int)fileData.at(j).Data.at(4)) * 16 + (unsigned int)fileData.at(j).Data.at(5);

            lc++;

        default:
            break;

            break;
        case RECORD_DATA_TYPE_SLA:
            ///printf("\nsla");
            break;
        }
    }

   
    fileData.clear();
    fileData.shrink_to_fit();
    for (unsigned int e = 0; e < lc; e++)
    {
        for (unsigned int i = 0; i < NO_OF_NPAGES; i++)
        { //if(i==4)
            ///    if(myNewPages[i].hasData==true)
            {

                myNewFilePageData[lc].myNewPages[i].hasData = false;
                for (int c = 0; c < 256; c++)
                {
                    if (myNewFilePageData[lc].myNewPages[i].binaryData[c] < 0xff)
                    {
                        myNewFilePageData[lc].myNewPages[i].hasData = true;
                        break;
                    }
                }
            }
        }
    }

    printf("%.2X %.2X\n", addresshigh, addresslow);
    for (int c = fromIndex; c < (toIndex + fromIndex); c++)
    {

        if (c % 16 == 0)
            printf("\n");
        printf("%.2X", myNewFilePageData[addresshigh].myNewPages[addresslow].binaryData[c]);
    }
}
