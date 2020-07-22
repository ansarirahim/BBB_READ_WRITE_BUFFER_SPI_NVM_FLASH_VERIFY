//Following is the program is developped by A. R. Ansari 
//It will read intel hex file having no extended linear address that is it has maxlimit of 0xFFFF addressing 64K Bytes..16 bit.
//example of use  in windows where first argument is filnename, 2nd argument is hex address ,3rd argument is in hex index of page and the last argument is in decimal the number of bytes to be read from the provided index of page...
//it shoudld be note that  2nd arg+ 3rd arg=>256 bytes otherwise it will rounded up under 256.
//DataRetriveFromIntelBuffer16.exe 0010603_NVM.HEX 36 51 16
//Expected out as follows:
//36
//01000A006400E803E803000100000100
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
unsigned int temp = 0;
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
#define NO_OF_NPAGES 400
newPage myNewPages[NO_OF_NPAGES];
void initDataStructures(newPage arnew[], unsigned int y)
{
    for (unsigned int i = 0; i < y; i++)
    {
        arnew[i].hasData = false;
        memset(arnew[i].binaryData, 0xff, 256);
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
int main(int argc, char *argv[])

{

    for (int i = 0; i < 2; i++)
        myBytes[i] = argv[2][i];
    addresslow = hex2byte(myBytes); //ParseByte(myBytes);

    for (int i = 0; i < 3; i++)
        myBytes[i] = argv[3][i];

    fromIndex = hex2byte(myBytes); //ParseByte(myBytes);

    if (fromIndex >= 256)
        fromIndex = 255;
    toIndex = atoi(argv[4]);
    if (toIndex + fromIndex > 256)
        toIndex = 1;
    initDataStructures(myNewPages, NO_OF_NPAGES);

    if (argc != 5)
    {
        printf("\nNACK");
        return 0;
    }
    char fileName[100];
    for (int i = 0; i < 100; i++)
    {
        fileName[i] = argv[1][i];
        if (argv[1][i] == '\0')
            break;
    }

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
                    myNewPages[pageNo].binaryData[i + pageIndex] = fileData.at(j).Data.at(4 + i);
                }
                else
                {
                    myNewPages[pageNo + 1].binaryData[i + pageIndex] = fileData.at(j).Data.at(4 + i);
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

            //             structExAddDet.extLinearAddress = extendedLA;

            //             if(extendedLA)
            //             {
            //                  pageCounter = 0;
            //         if(pageCounter)
            // extLACounter++;
            lc++;
            //  ///vExtendedLinearDetails.push_back(structExAddDet);
            //             }
            //   vExtendedLinearDetails.at(extLACounter).extLinearAddress=extendedLA;
            ///  printf("\nExtLA=%u EXTLAC=%u PC=%u ", extendedLA,lc, pageCounter);

        default:
            break;

            break;
        case RECORD_DATA_TYPE_SLA:
            ///printf("\nsla");
            break;
        }
    }

    //printf("\n");
    ////system("cls");
    fileData.clear();
    fileData.shrink_to_fit();
    for (unsigned int i = 0; i < NO_OF_NPAGES; i++)
    { //if(i==4)
        ///    if(myNewPages[i].hasData==true)
        {

            myNewPages[i].hasData = false;
            for (int c = 0; c < 256; c++)
            {
                if (myNewPages[i].binaryData[c] < 0xff)
                {
                    myNewPages[i].hasData = true;
                    break;
                }
            }
        }
    }

    printf("%.2X\n", addresslow);
    for (int c = fromIndex; c < (toIndex + fromIndex); c++)
    {

        printf("%.2X", myNewPages[addresslow].binaryData[c]);
        if (c % 16 == 0)
            printf("\n");
    }
}

