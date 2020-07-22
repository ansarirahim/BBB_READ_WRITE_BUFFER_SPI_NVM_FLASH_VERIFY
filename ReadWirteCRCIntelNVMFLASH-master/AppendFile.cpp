#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h> 
#include <fstream>
#define LINE_LENGTH 1000
#define FILENAME_LENGTH 100

using namespace std;
char line[1000];
int main(int argc, char **argv)

{
     if (argc != 3)
    {
        printf("\nNACK");
        return 0;
    }
    char fileName[FILENAME_LENGTH];
    for (int i = 0; i < 100; i++)
    {
        fileName[i] = argv[1][i];
        if (argv[1][i] == '\0')
            break;
    }
    for (int i = 0; i < LINE_LENGTH; i++)
    {
        line[i] = argv[2][i];
        if (argv[2][i] == '\0')
            break;
    }
    cout<<line<<endl;
    //std::ofstream ost {fileName, std::ios_base::app};
    fstream f(fileName, f.out | f.app);
    f<<line<<endl;

    // //ofstream writer(fileName , ios::app);

    // if (!writer)
    // {
    //     cout << "Error Opening File" << endl;
    //     return -1;
    // }

    // string info = "insert text here";
    // writer.append(info);

    // writer << info << endl;
    // writer.close();
    return 0;   
} 
