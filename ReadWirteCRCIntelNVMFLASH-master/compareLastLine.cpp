#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

int main(int argc, char **argv) {
    std::string result = "";
    std::ifstream fin(argv[1]);//"0010603_FLASH.HEX");

    if(fin.is_open()) {
        fin.seekg(0,std::ios_base::end);      //Start at end of file
        char ch = ' ';                        //Init ch not equal to '\n'
        while(ch != '\n'){
            fin.seekg(-2,std::ios_base::cur); //Two steps back, this means we
                                              //will NOT check the last character
            if((int)fin.tellg() <= 0){        //If passed the start of the file,
                fin.seekg(0);                 //this is the start of the line
                break;
            }
            fin.get(ch);                      //Check the next character
        }

        std::getline(fin,result);
        fin.close();
if((result==":00000001FF")||(result==":00000001FF\r"))//:00000001FF")
{std::cout<<"File is ok"<<std::endl;

return 0;
}
else
{
std::cout<<"file is not ok"<<std::endl;
return -1;
}
        std::cout << "final line length: " << result.size() <<std::endl;
        std::cout << "final line character codes: ";
        for(size_t i =0; i<result.size(); i++){
            std::cout << std::hex << (int)result[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "final line: " << result <<std::endl;
    }

    return 0;
}
