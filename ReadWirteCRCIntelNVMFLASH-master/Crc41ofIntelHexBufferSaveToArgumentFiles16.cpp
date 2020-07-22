
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#define LINE_LENGTH 1000
#define FILENAME_LENGTH 100

using namespace std;
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
//#define MAIN_PATH "\CS\"
#define PATH_OF_CRC "CRC41"
#define PATH_OF_BITS "BITS"
#define PATH_OF_MEMORY "MEMORY"
#define PATH_OF_SPEED "SPEED"
#define SIZE_OF_FILE_NAME_CS 20
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
static BYTE tempPageData[256];
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
void initDataStructures(newPage arnew[], unsigned int y)
{
    for (unsigned int i = 0; i < y; i++)
    {
        arnew[i].hasData = false;
        memset(arnew[i].binaryData, 0xff, 256);
    }
}
static char myBytes[2];
unsigned char hex2byte(const char *hex)
{
    unsigned short byte = 0;
    std::istringstream iss(hex);
    iss >> std::hex >> byte;
    return byte % 0x100;
}
BYTE getNVM_CRC(BYTE *CKBlock, BYTE Seed) // uint32_t Length, BYTE Seed)
{
    BYTE val, y, crc, bbit1;
    uint32_t k;
    crc = Seed;
    for (k = 0; k < 256; k++)
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

#define SIZE_OF_FILE_NAME 10
#define NO_OF_CS 4
//char fileName[SIZE_OF_FILE_NAME];
 struct csFileName
{
    char filename[SIZE_OF_FILE_NAME_CS];
    //bool fileEnable;
};
csFileName csFileNames[NO_OF_CS];


 struct CS_property_path
{
    char crcFile[10];
    char bitsFile[10];
    char memoryTypeFile[10];
    char speedFile[10];
};
static CS_property_path csProperties[NO_OF_CS];
#define NO_OF_EXTENDED_LA 20
BYTE extendedLAs[NO_OF_EXTENDED_LA];
static int SerachCharInArray(char *s, char c)
{
    for(int i=0;i<100;i++)
{
    if(s[i]=='\0')
return 0;
    if(s[i]==c)
return 1+i;


}
}
// static int FindSubCha(char *str,char *substr,int n)

// {int found=0;
//      for(int i=0;i<100;i++)
//     {
//         if((substr[i]=='\0'))
//         {
//             return found;
//         }

// found=SerachCharInArray(str,str,n);
//     }

// }

int main(int argc, char *argv[])

{
static char memType[5];
    
    initDataStructures(myNewPages, NO_OF_NPAGES);

    if (argc < 2) //5)
    {
        printf("\nNACK");
        return 0;
    }
    for (int ni = 0; ni < NO_OF_CS; ni++)
    {

       // csFileNames[ni].fileEnable = false;
        memset(csFileNames[ni].filename,'\0',SIZE_OF_FILE_NAME_CS);
    }

    for (int noargc = 2; noargc < argc; noargc++)
    {
        for (int i = 0; i < 100; i++)
        {

            csFileNames[noargc - 2].filename[i] = argv[noargc][i];
            if (argv[noargc][i] == '\0')
            {
             //   csFileNames[noargc - 1].fileEnable = true;
                break;
            }
        }
    }

    ///
     char fileName[100];
    for (int i = 0; i < 100; i++)
    {
        fileName[i] = argv[1][i];
        if (argv[1][i] == '\0')
            break;
    }
if(SerachCharInArray(fileName, 'N')&&SerachCharInArray(fileName, 'V')&& SerachCharInArray(fileName, 'M'))
sprintf(memType,"%s","NVM");
else
if(SerachCharInArray(fileName, 'F')&&SerachCharInArray(fileName, 'L')&& SerachCharInArray(fileName, 'A')&& SerachCharInArray(fileName, 'S')&& SerachCharInArray(fileName, 'H'))
sprintf(memType,"%s","FLASH");

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
extendedLAs[lc]=extendedLA;
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
    int max=0;
    for(int i=0;i<lc;i++)
    {
        if(max<extendedLAs[i])
       
        {
                max=extendedLAs[i];
        }
        
    }
   // printf("\nNumber of extendedLA=%d and max la=%d",lc,max);
     switch(max)
     {
         case 0 :
            max=16;
            break;
     }
    // printf("\n24 Bit Addressing is required");
    // else
    // printf("\n16Bit");
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
    BYTE Crc = 80;

    for (unsigned int i = 0; i < 0x100; i++)
    {

        Crc = getNVM_CRC(myNewPages[i].binaryData, Crc);
    }

   /// printf("CRC41_16=0x%.2X\n", Crc);
      for (int ig = 0; ig < NO_OF_CS; ig++)
    { 
        
      //  if (csFileNames[ig].fileEnable)
     if(csFileNames[ig].filename[0]!='\0')
        { memset(fileName,'\0',100);
        sprintf(fileName,"/root/BBB_INTEL_HEX_FORMAT_SPI/BITS.%s",csFileNames[ig].filename);
            //printf("Clear and updated at %d %s\n", ig,csFileNames[ig].filename);
            fstream f2(fileName, f2.out | f2.trunc);
            //f2.close();
           // fstream f10(csFileNames[ig].filename, f10.out | f10.app);
            f2 << (unsigned int)max << endl;
           //  f10.close();
            f2.close();
        }
    }
  for (int ig = 0; ig < NO_OF_CS; ig++)
    { 
        
      //  if (csFileNames[ig].fileEnable)
     if(csFileNames[ig].filename[0]!='\0')
        { memset(fileName,'\0',100);
        sprintf(fileName,"/root/BBB_INTEL_HEX_FORMAT_SPI/MEMORY_TYPE.%s",csFileNames[ig].filename);
            //printf("Clear and updated at %d %s\n", ig,csFileNames[ig].filename);
            fstream f2(fileName, f2.out | f2.trunc);
            //f2.close();
           // fstream f10(csFileNames[ig].filename, f10.out | f10.app);
            f2 << memType << endl;
           //  f10.close();
            f2.close();
        }
    }

    // for(int i=0;i<NO_OF_CS;i++)
    // printf("\nfile=%s",csFileNames[i].filename);

   
    for (int ig = 0; ig < NO_OF_CS; ig++)
    { 
        if(csFileNames[ig].filename[0]!='\0')
        //if (csFileNames[ig].fileEnable)
        { //memset(fileName,'\0',100);
       // sprintf(fileName,"CRC41_%s",csFileNames[ig].filename);
        memset(fileName,'\0',100);
        sprintf(fileName,"/root/BBB_INTEL_HEX_FORMAT_SPI/CRC41.%s",csFileNames[ig].filename);
         ///   printf("\n\nClear and updated at %d %s\n",ig,csFileNames[ig].filename);// fileName);//ig,csFileNames[ig].filename);
            fstream f2(fileName, f2.out | f2.trunc);
            //f2.close();
           // fstream f10(csFileNames[ig].filename, f10.out | f10.app);
            f2 << (unsigned int)Crc << endl;
            // f10.close();
            f2.close();
        }
    }
}

