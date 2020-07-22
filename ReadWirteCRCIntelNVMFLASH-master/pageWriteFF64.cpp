#include <cstring>
#include <iostream>


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

addressmid=atoi(argv[1]);
    static BYTE pages128[128];
static int ret = 0;
static	int fd;
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

	//puts("");
	//printf("The spi mode is set to: %d\n", mode); //output successful settings to the terminal
	//printf("Bits per word: %d\n", bits);
	speed = 10000;
	//printf("Max speed is set to: %d Hz (%d KHz) (%d MHz)\n", speed, speed / 1000, speed / 1000000);

////////////////
//BYTE yed=80;
//////////CRC//
memset(pages128,0xff,128);
   //for (unsigned int i = 0; i < 256;i++)///NO_OF_NPAGES; i++)
    { 
//          if(myNewPages[i].hasData==true)
        {

            //////////////////////////////////
for (int page128=0;page128<2;page128++)
{
//addresshigh =i;//vPageDetails.at(i).extendedLinearAdderess;// Spi_address >> 16; //
//			addressmid =i;// vPageDetails.at(i).pageNo;//Spi_address >> 8;	 //
			//addresslow = 0;//Spi_address;
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
///printf("\nAddress=%.2x %.2x",addressmid,addresslow);
/*
for( int m=0;m<128;m++)
{pages128[m]=myNewPages[i].binaryData[m+addresslow];//vPageDetails.at(i).pageData[m+addresslow];

// printf("%.2X",pages128[m]);
// if(m%16==0)
// printf("\n");
}*/

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
			usleep(3000);


 }
         
        }
    }

   /// printf("CRC41_16=0x%.2X\n", Crc);
  
}

