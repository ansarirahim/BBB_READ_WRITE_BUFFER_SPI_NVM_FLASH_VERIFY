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

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "iosfwd"
#include <iostream>
#include <iostream>
#include "SimpleGPIO_SPI.h"
#include "SPI_SS_Def.H"
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//#include <spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
using std::cout;
using std::endl;
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




#define CLK_PER_SEC_ACTUAL (99000)
static void AllFlashChipsSelect(PIN_VALUE x)
{
	//////gpio_set_value_spi(SS2, x);
	//////gpio_set_value_spi(SS0, x);
	//////gpio_set_value_spi(SS4, x);
	//////gpio_set_value_spi(SS6, x);
}
void msleep(int ms)
{
	struct timespec ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;

	nanosleep(&ts, NULL);
}
bool SearchForData(uint8_t *buff, long size)
{
	for (long i = 0; i < size; i++)
	{
		if (buff[i] < 0xff)
			return true;
	}
	return false;
}

#define FLASH_CERS 0xC7
#define FLASH_SE 0xD8
//definitions for AT25512 device
#define WRITE_CYCLE_TIME (5000) //AT25512 write cycle time in us
#define WRSR (0x01)				//AT25512 write status register
#define WRITE (0x02)			//AT25512 write data to memory array
#define READ (0x03)				//AT25512 read data from memory array
#define WRDI (0x04)				//AT25512 reset write enable latch
#define RDSR (0x05)				//AT25512 read status register
#define WREN (0x06)				//AT25512 set write enable latch
static void pabort(const char *s)
{
	perror(s);
	abort();
}

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
int main(int argc, char **argv)
{
//char *end=":00000001FF";
//char *pcmp=NULL;
    if (argc != 2)
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
//:00000001FF:00000001FF:00000001FF

//else
//exit(0);
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);

        lineCounter++;
    }
   BYTE lc=0;
    int checkSumIndex = 0;
    BYTE checkSum = 0;
    for (int j = 0; j < lineCounter; j++)
    {
        // printf("\n");

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
            

                ////printf("\nretreived Pageno =%.2X Retrived pageindex=%.2X,eLA=%u",pageNo,pageIndex,extendedLA);

                for (int i = 0; i < fileData.at(j).Data.at(DATA_LENGTH); i++)
                {
                    /// printf("%.2X",fileData.at(j).Data.at(4+i));
                    tempPageData[pageIndex + i] = fileData.at(j).Data.at(4 + i);
                    if (tempPageData[pageIndex + i] < 0xff)
                        dataPresent = true;
                    ///    if((pageIndex%16==0) ||(pageIndex==255))
                    
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
///////////////////
BYTE pages128[128];
int ret = 0;
	int fd;
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 100000; //need to be speeded up when working
static uint16_t delay = 5;
fd = open("/dev/spidev1.0", O_RDWR); //open the spi device
	if (fd < 0)
		pabort("can't open device");

	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode); //set the spi mode
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode); //get the spi mode (test)
	if (ret == -1)
		pabort("can't get spi mode");

	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits); //set the spi bits per word
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits); //get the spi bits per word (test)
	if (ret == -1)
		pabort("can't get bits per word");

	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed); //set the spi max speed
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed); //get the spi max speed (test)
	if (ret == -1)
		pabort("can't get max speed hz");

	puts("");
	printf("The spi mode is set to: %d\n", mode); //output successful settings to the terminal
	printf("Bits per word: %d\n", bits);
	speed = 10000;
	printf("Max speed is set to: %d Hz (%d KHz) (%d MHz)\n", speed, speed / 1000, speed / 1000000);

////////////////
BYTE yed=80;
//////////CRC//
char addressmid=0;
char addresslow=0;
char addresshigh=0;
for(unsigned int i=0;i<vPageDetails.size();i++)
 {
//printf("\n%.2X %.2X\n",vPageDetails.at(i).extendedLinearAdderess,vPageDetails.at(i).pageNo);

//////////////////////////////////
for (int page128=0;page128<2;page128++){
addresshigh =vPageDetails.at(i).extendedLinearAdderess;// Spi_address >> 16; //
			addressmid = vPageDetails.at(i).pageNo;//Spi_address >> 8;	 //
			addresslow = 0;//Spi_address;
			///printf("\nWriting..Adress=%.2X %.2X%.2X, Adress=%ld",addresshigh, addressmid,addresslow,Spi_address );
			char writeenable[1] = {
				WREN,
			};
if(page128)
addresslow=128;
else
addresslow=0;
			char writecommand[3] = {
				WRITE,
//				addresshigh,
				addressmid,
				addresslow,
			};
printf("\n\nAdre-%.2X %.2X %.2X\n",vPageDetails.at(i).pageNo,addressmid,addresslow);
for( int m=0;m<128;m++)
{pages128[m]=vPageDetails.at(i).pageData[m+addresslow];

printf("%.2X",pages128[m]);
if(m%16==0)
printf("\n");
}

			///setcharbuffer(TemCharBuffer,256,set);

			struct spi_ioc_transfer message[1] = {
				0,
			}; //setup spi transfer data structure

			message[0].tx_buf = (unsigned long)writeenable; //send the write enable command
			message[0].rx_buf = (unsigned long)NULL;
			message[0].len = sizeof(writeenable);
			message[0].cs_change = 0;
			//chip select needs to be released
			usleep(500);
			//////gpio_set_value_spi(SS6, LOW);
			ret = ioctl(fd, SPI_IOC_MESSAGE(1), &message); //spi check if sent
			if (ret < 1)
				pabort("can't send spi message");
			///////////////////////////////////////////////////////
			struct spi_ioc_transfer message1[2] = {
				0,
			}; //setup spi transfer data structure

			message1[0].tx_buf = (unsigned long)writecommand; //send the write command and address
			message1[0].rx_buf = (unsigned long)NULL;
			message1[0].len = sizeof(writecommand);
			message1[0].cs_change = 0;
			message1[1].tx_buf = (unsigned long)pages128;//vPageDetails.at(i).pageData;//
			; //data;//TempByteBuffer;//data;         //send the data
			message1[1].rx_buf = (unsigned long)NULL;
			message1[1].len =128;//256;// sizeof(vPageDetails.at(i).pageData); //data);//TempByteBuffer);
			message1[1].cs_change = 0;;							//release the chip select line
			usleep(5000);

			ret = ioctl(fd, SPI_IOC_MESSAGE(2), &message1); //spi check if sent
			if (ret < 1)
				pabort("can't send spi message");
			usleep(50000);

////////////////////////////////////
  /* for(int k=0;k<256;k++)
{
if(k%16==0)
printf("\n");
printf("%.2X",vPageDetails.at(i).pageData[k]);
}*/ 
   //yed = getNVM_CRC(vPageDetails.at(i).pageData, 256, yed);  
 }
}
close(fd);
// printf("\n\nCRC41 of Data=0x%.2X i=%d linceCounter=%u exc=%u pgc=%u\n",yed,vPageDetails.size(),lineCounter,lc,pageCounter);

 ///
// printf("\nfileData Size=%u",fileData.size());
// vPageDetails.shrink_to_fit();
//  printf("\nExtLA=%u PC=%u,vPageDetails=%u", lc, pageCounter,vPageDetails.size());

//  //printf("\n");
 


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
