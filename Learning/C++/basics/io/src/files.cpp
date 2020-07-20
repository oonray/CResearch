#include <cstdio>
#include <iostream>
#include <fstream>


int main(){
    std::string data;
    std::fstream fileA("./textfile.txt");
    std::string supply[10];
    int qty[10];
    int i = 0;

    if(fileA.fail()){
        printf("Could not open textfile.txt\n");
        return 1;
    }

    while(fileA >> data){
        std::cout << data << " ";
    }
    std::cout << "\n";

    fileA.close();
    return 0;
}
