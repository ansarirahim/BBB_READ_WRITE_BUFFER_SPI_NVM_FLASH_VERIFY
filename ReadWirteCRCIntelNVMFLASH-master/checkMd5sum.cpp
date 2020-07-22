#include<stdio.h>
//#include<cstring.h>


//md5sum -c checkmd5.md5
#include <stdio.h>
#define PATH_CHKSUM "/root/BBB_INTEL_HEX_FORMAT_SPI/"
#include<stdlib.h>
#include<cstring>
char fileName[100];
char fullFilname[100];
char cmdBuffer[100];

int main(int argc , char ** argv)
{
//string pc=PATH_CHKSUM;
for (int i = 0; i < 100; i++)
    {
        fileName[i] = argv[1][i];
        if (argv[1][i] == '\0')
            break;
    }

memset(cmdBuffer,'\0',100);

sprintf(cmdBuffer,"md5sum -c %s%s.md5",PATH_CHKSUM,fileName);
if(system(cmdBuffer)==0)


return 0;
else
return 1;
//printf(cmdBuff
}
