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
unsigned pageRepeater=0;
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






BYTE extLACounter=0;
unsigned int  pageCounter=0;
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
char addresshigh,addressmid,addresslow;
int fromIndex,toIndex;
int main(int argc, char *argv[])

{
  //      int ret = 0;
    //    int fd;
///     Spi_address = 256 * atol(argv[1]);
addresshigh=atoi(argv[2]);
addressmid=atoi(argv[3]);
addresslow=atoi(argv[4]);
fromIndex=atoi(argv[5]);
if(fromIndex>=256)
fromIndex=255;
toIndex=atoi(argv[6]);
if(toIndex+fromIndex>256)
toIndex=1;



///printf("\nfi=%d toi=%d",fromIndex,toIndex);
//int main(int argc, char **argv)
//{
//char *end=":00000001FF";
//char *pcmp=NULL;
    if (argc != 7)
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
//address

    //argv[1];
///    requestedELA = atol(argv[2]);
   /// requestedPageNo = atol(argv[3]);
    ///int fromIndex = atol(argv[4]) % 256;
    ///int toIndex = atol(argv[5]) % 256;

    ///printf("\nrequestedELA =%.2X requestedPageNo=%.2X",requestedELA,requestedPageNo);
    ///

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

    // Store data read from file, line by line
    vector<LineData> fileData;
    vector<pageDetails> vPageDetails;
  

    // struct pageData
    // {
    //     BYTE page[256];
    //     unsigned int pageNo;
    //     unsigned int exAddres;
    // };
    // vector <pageData> myPageData;
    // Read file line by line, and process it
    bool endOfFile = false;
    bool dataPresent = true;
    while (getline(inFile, line))
    {

        LineData currLineData;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);

        lineCounter++;
    }
   BYTE lc=0;
    int checkSumIndex = 0;
    BYTE checkSum = 0;
    for (int j = 0; j < lineCounter; j++)
    {
//        printf("\nlinecounter=%u",lineCounter);

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

            ///if((extendedLA==requestedELA)&&(pageNo==requestedPageNo))
            

         ///printf("\nretreived Pageno =%.2X Retrived pageindex=%.2X,eLA=%u",pageNo,pageIndex,extendedLA);

                for (int i = 0; i < fileData.at(j).Data.at(DATA_LENGTH); i++)
                {
                    /// printf("%.2X",fileData.at(j).Data.at(4+i));
        tempPageData[pageIndex + i] = fileData.at(j).Data.at(4 + i);
                    if (tempPageData[pageIndex + i] < 0xff)
                        dataPresent = true;
                    ///    if((pageIndex%16==0) ||(pageIndex==255))
             

if(pageNo==4)
                 {printf("\nPageNo=%u,%u",pageNo,pageRepeater);
                                        pageRepeater++;}

       
                        if ((pageIndex + i) == 255)
                        {

                            //     vExtendedLinearDetails.at(extLACounter-1).vPageDetails.push_back(pDetails);

                            if (dataPresent == true)
                            {

                                struct pageDetails pDetails;
                                pDetails.pageNo = pageNo;
                                pDetails.extendedLinearAdderess=extendedLA;
                                for (int pg = 0; pg < 256; pg++)
                                {

                                    pDetails.pageData[pg] = tempPageData[pg];
                                    //  vExtendedLinearDetails.at(extLACounter-1).vPageDetails.at(pageCounter).pageData[pg]=tempPageData[pg];
                                }
                                vPageDetails.push_back(pDetails);
                                //structExAddDet.vVPageDetails.at(pageCounter).vPageDetails.push_back(pDetails);

                                pageCounter++;
                            }
                            dataPresent = false;
                            //break;
                        }
                    }
                    //  temp++;
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
BYTE yed=80;
//////////CRC//
//////////
/*
for(unsigned int i=0;i<vPageDetails.size();i++)
 {
//if(addresshigh==vPageDetails.at(i).extendedLinearAdderess)
{
//	if(addressmid==vPageDetails.at(i).pageNo)
{
printf("(HEX DUMP)=>%.2X %.2X %.2X %.3X\n",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo,fromIndex,toIndex);
   for(int k=fromIndex;k<(fromIndex+toIndex);k++)
	{
	if(k%16==0)
	printf("\n");
	printf("%.2X",vPageDetails.at(i).pageData[k]);
	} 

///   yed = getNVM_CRC(vPageDetails.at(i).pageData, 256, yed);  
}
} 
}
*/

///////

/*

//printf("\nRequested extAdres=%d mid=%d fi=%d toi=%d",addresshigh,addressmid,fromIndex,toIndex);
for(unsigned int i=0;i<vPageDetails.size();i++)
 {
if(addresshigh==vPageDetails.at(i).extendedLinearAdderess)
{
	if(addressmid==vPageDetails.at(i).pageNo)
{
printf("(HEX DUMP)=>%.2X %.2X %.2X %.3X\n",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo,fromIndex,toIndex);
   for(int k=fromIndex;k<(fromIndex+toIndex);k++)
	{
	if(k%16==0)
	printf("\n");
	printf("%.2X",vPageDetails.at(i).pageData[k]);
	} 

///   yed = getNVM_CRC(vPageDetails.at(i).pageData, 256, yed);  
}
} 

}
*/

 //printf("\n\nCRC41 of Data=0x%.2X i=%d linceCounter=%u exc=%u pgc=%u\n",yed,vPageDetails.size(),lineCounter,lc,pageCounter);
 ///
// printf("\nfileData Size=%u",fileData.size());
// vPageDetails.shrink_to_fit();
//  printf("\nExtLA=%u PC=%u,vPageDetails=%u", lc, pageCounter,vPageDetails.size());

printf("\n");
 


//  for(unsigned int i=0;i<vPageDetails.size();i++)
//  {
//      if((requestedELA==vPageDetails.at(i).extendedLinearAdderess)&& (vPageDetails.at(i).pageNo==requestedPageNo)){
//    printf("\n")  ;
// printf("%.2X%.2X",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo);
// for(int k=fromIndex;k<toIndex;k++)
// {
//     if(k%16==0)
// printf("\n");
//      printf("%.2X",vPageDetails.at(i).pageData[k]);
    
    
   
// }

// }
     
//  }
// for(int i=fromIndex;i<=toIndex;i++){
// if(i%16==0)
// printf("\n");
// printf("%.2X",tempPageData[i]);
// }
//     for(int k=0;k<1;k++){
// for(int j=0 ;j<1;j++)
//     for(int pg=0;pg<256;pg++){
//      printf("%.2X",vExtendedLinearDetails.at(k).vPageDetails.at(j).pageData[pg]);
//      if(pg%16==0)
//      printf("\n");
//                         }

//     }
}
