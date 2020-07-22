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

//00000001FF

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
/*
void compareOperation(string s1, string s2) 
{ 
    // returns a value < 0 (s1 is smaller then s2) 
    if((s1.compare(s2)) < 0) 
        cout << s1 << " is smaller than " << s2 << endl; 
  
    // returns 0(s1, is being comapared to itself) 
    if((s1.compare(s1)) == 0) 
        cout << s1 << " is equal to " << s1 << endl; 
    else
        cout << "Strings didn't match "; 
      
} */

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
/*
void goToLastLine()
{
char * data1,data2,data3;
	fstream file; // If you don't know what std::fstream is, look it up
	file.open(filename);
	if(!file.is_open())
	{
		cout << "Problem opening file.\n";
		return 2;
	}
	file.seekg(EOF); // go to the end of file
	while(true)
	{
		file.unget(); //go back two chars
		file.unget();
		char in = file.get();
		if(in == '\n')
		{
                        //get line from file until space is encountered and put it in data1
			file.getline(data1,' ');
                        file.getline(data2,' '); //etc
                        file.getline(data3,' ');//etc
			break;
		}
	}
        //send the data to the output stream
	cout << "Data: " << data1 << " " << data2 << " " << data3 << endl; 
        //end program

}*/
char cmdBuffer[100];
int main(int argc, char *argv[])

{
  
addresshigh=atoi(argv[2]);
addressmid=atoi(argv[3]);
addresslow=atoi(argv[4]);
fromIndex=atoi(argv[5]);
if(fromIndex>=256)
fromIndex=255;
toIndex=atoi(argv[6]);
if(toIndex+fromIndex>256)
toIndex=1;




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
memset(cmdBuffer,'\0',100);
//char cmdBuffer[100];
char cmd[]="./compareLastLine ";
sprintf(cmdBuffer,"%s %s",cmd,fileName);
    ifstream inFile(fileName); //0010603_FLASH.HEX"); //InputFile.txt");

    // Check for open failure
    if (!inFile)
    {
        cout << "Can't open file." << endl;
        exit(1);
    }
///goToLastLine();
    // Line read from file
   std::string line;


    vector<LineData> fileData;
    vector<pageDetails> vPageDetails;
  


    bool endOfFile = false;
    bool dataPresent = true;
//string endoffilestring=":00000001FF\r";
    while (getline(inFile, line))
//do
    {
if((":00000001FF\r"==line)||(":00000001FF"==line))//endoffilestring==line)
{//cout<<"File is finished"<<endl;
endOfFile=true;
//break;
}
        LineData currLineData;
//cout<<lineCounter<<"**"<<line<<endl;;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);

        lineCounter++;
    }
//cout<<"Last line="<<line<<endl;
//while (getline(inFile, line));
   BYTE lc=0;

if(endOfFile==false)
{
    printf("\nDidn't find End of File=%u",lineCounter);
      exit(0);
}
//else
//printf("\nFile read till last line");
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
           
            if (checkSum != fileData.at(j).Data.at(checkSumIndex))
            {
                printf("\nCheckSum Error @LineNo= %u %.2X ", j, checkSum);
                exit(0);
            }


                for (int i = 0; i < fileData.at(j).Data.at(DATA_LENGTH); i++)
                {
                  
                    tempPageData[pageIndex + i] = fileData.at(j).Data.at(4 + i);
                    if (tempPageData[pageIndex + i] < 0xff)
                        dataPresent = true;
                 
                    
                        if ((pageIndex + i) == 255)
                        {

                           

                            if (dataPresent == true)
                            {

                                struct pageDetails pDetails;
                                pDetails.pageNo = pageNo;
                                pDetails.extendedLinearAdderess=extendedLA;
                               

                                for (int pg = 0; pg < 256; pg++)
                                {

                                    pDetails.pageData[pg] = tempPageData[pg];
                                    
                                }
                                vPageDetails.push_back(pDetails);
                               

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
             // printf("\n EOF is found");       

if(fileData.at(j).Data.at(RECORD_DATA_TYPE_INDEX+1)==0xff)
endOfFile=true;
            break;
        case RECORD_DATA_TYPE_ESA:
            /// printf("\nesa");
            break;
        case RECORD_DATA_TYPE_ELA:

            extendedLA = ((unsigned int)fileData.at(j).Data.at(4)) * 16 + (unsigned int)fileData.at(j).Data.at(5);
if(extendedLA>0)
printf("\nAddress is 24 bit");
else
printf("\nAddress is 16 bit");


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
BYTE yed=80;
if(!endOfFile)
{
printf("\n Didn't find Intel Hex Format End_OF_File protocol");
exit(0);

}
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


}
} 
}


 
printf("\n");
 



}
