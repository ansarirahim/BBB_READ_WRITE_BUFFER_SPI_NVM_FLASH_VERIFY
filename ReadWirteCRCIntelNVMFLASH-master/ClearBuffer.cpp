#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
#define LINE_LENGTH 1000
#define FILENAME_LENGTH 100

using namespace std;
//char line[1000];
int main(int argc, char **argv)

{
     if (argc != 2)
    {
        printf("NACK\n");
        return 0;
    }
    char fileName[FILENAME_LENGTH];
    for (int i = 0; i < 100; i++)
    {
        fileName[i] = argv[1][i];
        if (argv[1][i] == '\0')
            break;
    }

  if( remove( fileName ) != 0 )
    perror( "ACK\n" );
  else
    puts( "ACK\n" );
  return 0;
}
